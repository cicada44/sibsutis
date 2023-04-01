#include <omp.h>

#include <ctype.h>

#include <stdlib.h>
#include <stdio.h>

void *vmalloc(size_t nb)
{
    void *dest = malloc(nb);

    if (dest == NULL)
    {
        exit(-1);
    }

    return dest;
}

double *matrix_vector_product(double *a, double *b, const size_t m, const size_t n, double *time)
{
    double *c = vmalloc(sizeof(double) * m * n);

    *time = omp_get_wtime();
    for (int i = 0; i < m; i++)
    {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];
    }
    *time = (omp_get_wtime() - *time);

    return c;
}

int verify(double *c1, double *c2, const size_t m, const size_t n)
{
    for (size_t i = 0; i != m; ++i)
    {
        if (c1[i] != c2[i])
        {
            return 0;
        }
    }

    return 1;
}

void calc_dgemv(double *a, double *b, double *c, const size_t m, const size_t n, const size_t threads)
{
    a = vmalloc(sizeof(double) * m * n);
    b = vmalloc(sizeof(double) * n);
    c = vmalloc(sizeof(double) * m);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            a[i * n + j] = i + j;
    }
    for (int j = 0; j < n; j++)
        b[j] = j;

    double t = omp_get_wtime();=
#pragma omp parallel num_threads(threads)
    {
        int n_threads = omp_get_num_threads();
        int curr_thread_num = omp_get_thread_num();
        int lines_on_thread = m / n_threads;
        int l_bound = curr_thread_num * lines_on_thread;
        int u_bound = (curr_thread_num == n_threads - 1) ? (m - 1) : (l_bound + lines_on_thread - 1);

        for (int i = l_bound; i <= u_bound; ++i)
        {
            for (int j = 0; j != n; ++j)
            {
                c[i] += a[i * n + j] * b[j];
            }
        }
    }

    t = (omp_get_wtime() - t);

    // printf("Matrix m: %ld\tElapsed time: %.6f\tThreads: %ld\n", m, t, threads);
    double time = 0;
    matrix_vector_product(a, b, m, n, &time);
    printf("%ld\t%.3f\n", threads, time / t);
    // printf("Size: %ld\tThreads: %ld\tSpeedup: %.3f\n", m, threads, time / t);
    // printf("Verification: ");
    // (verify(matrix_vector_product(a, b, m, n, &time), c, m, n) == 0) ? printf("FAIL\n") : printf("SUCCESS\n");
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Usage: ./benchmark <m> <n> <threads>\n");
        exit(-1);
    }

    double *a = NULL, *b = NULL, *c = NULL;

    calc_dgemv(a, b, c, atol(argv[1]), atol(argv[2]), atol(argv[3]));

    free(a);
    free(b);
    free(c);
}
