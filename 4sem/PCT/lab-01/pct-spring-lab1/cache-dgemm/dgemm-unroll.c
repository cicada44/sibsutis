#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifndef N
#define N 1024
#endif

double wtime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1E-9;
}

void matrix_init(double a[N][N], double b[N][N], double c[N][N])
{
    srand(0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0;
        }
    }
}

void dgemm_def(double a[N][N], double b[N][N], double c[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            } /* b[][] stride-N read */
        }
    }
}

void dgemm_verify(double a[N][N], double b[N][N], double c[N][N], const char *msg)
{
    double *c0 = malloc(sizeof(*c0) * N * N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            c0[i * N + j] = 0;
    }
    dgemm_def(a, b, (double (*)[N])c0);

    int failed = 0;
    for (int i = 0; i < N && !failed; i++) {
        for (int j = 0; j < N; j++) {
            double diff = fabs(c[i][j] - c0[i * N + j]);
            if (diff > 1E-6) {
                fprintf(stderr, "dgemm: %s: verification failed %.6f != %.6f\n", msg, c0[i * N + j], c[i][j]);
                failed = 1;
                break;
            }
        }
    }
    if (!failed) {
        fprintf(stderr, "dgemm: %s: verification passed\n", msg);
    }
    free(c0);
}

int main()
{
    #define SM 8 // 16 (64 / sizeof(double))
    #define L2 8 // 32 (64 / sizeof(double))
    #define L3 8 // 8 (64 / sizeof(double))

    long long int i, i2, j, j2, k, k2;

    double * __restrict__ res;
    double * __restrict__ mul1;
    double * __restrict__ mul2;

    res = malloc(N * N * sizeof(double));
    mul1 = malloc(N * N * sizeof(double));
    mul2 = malloc(N * N * sizeof(double));

    double t = wtime();
    for (i = 0; i < N; i += L2) {
        for (j = 0; j < N; j += SM) {
            for (k = 0; k < N; k += L3 ) {
                for (i2 = 0; i2 < L2 ; ++i2) {
                    for (k2 = 0; k2 < L3 ; ++k2) {
                        #pragma GCC ivdep
                        #pragma GCC unroll 8
                        for (j2 = 0; j2 < SM; ++j2) {
                            res[ i * N + j + j2] += mul1[i * N + k + k2] * mul2[k * N + j + j2];
                        }
                    }
                }
            }
        }
    }
    t = wtime() - t;
    printf("%d  %.6f  %.2f\n", N, t, 2.0 * N * N * N * 1E-9 / t);

    return 0;
}
