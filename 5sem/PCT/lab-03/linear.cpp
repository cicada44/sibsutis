#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <mpi.h>

enum { m = 45000, n = 45000 };
void dgemv(float* a, float* b, float* c, int m, int n)
{
    for (int i = 0; i < m; i++) {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];
    }
}

int main(int argc, char** argv)
{
    double t = MPI_Wtime();
    float *a, *b, *c;

    a = (float*)malloc(sizeof(float) * m * n);
    b = (float*)malloc(sizeof(float) * n);
    c = (float*)malloc(sizeof(float) * m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            a[i * n + j] = i + 1;
    }
    for (int j = 0; j < n; j++)
        b[j] = j + 1;

    dgemv(a, b, c, m, n);

    t = MPI_Wtime() - t;

    printf("Elapsed time (serial): %.6f sec.\n", t);

    free(a);
    free(b);
    free(c);
}