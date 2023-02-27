#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifndef CACHELINE_SIZE
#define CACHELINE_SIZE 64
#endif

#ifndef N
#define N 64
#endif

#define NREPS 3

/* Block (tail) size */
#define BS (CACHELINE_SIZE / sizeof(double))

double a[N][N]; // __attribute__ ((aligned(CLSIZE)));
double b[N][N]; // __attribute__ ((aligned(CLSIZE)));
double c[N][N]; // __attribute__ ((aligned(CLSIZE)));

int IMIN(int n1, int n2)
{
    return (n1 < n2) ? n1 : n2;
}

double wtime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1E-9;
}

void matrix_init(double a[N][N], double b[N][N], double c[N][N])
{
    srand(0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0;
        }
    }
}

void dgemm_def(double a[N][N], double b[N][N], double c[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            } /* b[][] stride-N read */
        }
    }
}

void dgemm_transpose(double a[N][N], double b[N][N], double c[N][N])
{
    double *tmp = malloc(sizeof(*tmp) * N * N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tmp[i * N + j] = b[j][i];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c[i][j] += a[i][k] * tmp[j * N + k];
            } /* tmp[] stride-1 read */
        }
    }
    free(tmp);
}

void dgemm_interchanged(double a[N][N], double b[N][N], double c[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            for (int j = 0; j < N; j++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void dgemm_block(double a[N][N], double b[N][N], double c[N][N])
{
    for (int ii = 0; ii < N; ii += BS)
    {
        for (int jj = 0; jj < N; jj += BS)
        {
            for (int kk = 0; kk < N; kk += BS)
            {
                for (int i = ii; i < IMIN(N, ii + BS); i++)
                {
                    for (int j = jj; j < IMIN(N, jj + BS); j++)
                    {
                        for (int k = kk; k < IMIN(N, kk + BS); k++)
                            c[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        }
    }
}

void dgemm_verify(double a[N][N], double b[N][N], double c[N][N], const char *msg)
{
    double *c0 = malloc(sizeof(*c0) * N * N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            c0[i * N + j] = 0;
    }
    dgemm_def(a, b, (double(*)[N])c0);

    int failed = 0;
    for (int i = 0; i < N && !failed; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double diff = fabs(c[i][j] - c0[i * N + j]);
            if (diff > 1E-6)
            {
                fprintf(stderr, "dgemm: %s: verification failed %.6f != %.6f\n", msg, c0[i * N + j], c[i][j]);
                failed = 1;
                break;
            }
        }
    }
    if (!failed)
    {
        fprintf(stderr, "dgemm: %s: verification passed\n", msg);
    }
    free(c0);
}

int main()
{
    double t1, t2, t3;

#if 0
    matrix_init(a, b, c);

    t1 = wtime();

    for (int i = 0; i < NREPS; i++)
    {
        dgemm_def(a, b, c);
    }

    t1 = wtime() - t1;

    t1 /= NREPS;

    printf("# DGEMM def: N=%d, elapsed time (sec) %.6f\n", N, t1);
#endif

#if 0
    matrix_init(a, b, c);

    t2 = wtime();

    for (int i = 0; i < NREPS; i++)
    {
        dgemm_interchanged(a, b, c);
    }

    t2 = wtime() - t2;

    t2 /= NREPS;

    printf("# DGEMM interchange: N=%d, elapsed time (sec) %.6f\n", N, t2);
#endif

#if 1
    matrix_init(a, b, c);

    t3 = wtime();

    for (int i = 0; i < NREPS; i++)
    {
        dgemm_block(a, b, c);
    }

    t3 = wtime() - t3;

    t3 /= NREPS;

    printf("# DGEMM bloc: N=%d, BS=%ld, elapsed time (sec) %.6f\n", N, BS, t3);
#endif

/* Verification */
#if 0

#if 0
    matrix_init(a, b, c);
    dgemm_interchange(a, b, c);
    dgemm_verify(a, b, c, "interchange");
#endif

#if 0
    matrix_init(a, b, c);
    dgemm_block(a, b, c);
    dgemm_verify(a, b, c, "block");
#endif

#endif
    return 0;
}
