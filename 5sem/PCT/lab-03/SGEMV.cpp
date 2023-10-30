#include <cmath>
#include <iostream>
#include <mpi.h>

void get_chunk(int a, int b, int commsize, int rank, int* lb, int* ub)
{
    /* OpenMP 4.0 spec (Sec. 2.7.1, default schedule for loops)
     * For a team of commsize processes and a sequence of n items, let ceil(n ? commsize) be the
     * integer q that satisfies n = commsize * q - r, with 0 <= r < commsize. Assign q iterations to
     * the first commsize - r procs, and q - 1 iterations to the remaining r processes */
    int n = b - a + 1;
    int q = n / commsize;
    if (n % commsize) q++;
    int r = commsize * q - n;
    /* Compute chunk size for the process */
    int chunk = q;
    if (rank >= commsize - r) chunk = q - 1;
    *lb = a;        /* Determine start item for the process */
    if (rank > 0) { /* Count sum of previous chunks */
        if (rank <= commsize - r)
            *lb += q * rank;
        else
            *lb += q * (commsize - r) + (q - 1) * (rank - (commsize - r));
    }
    *ub = *lb + chunk - 1;
}

void sgemv(float* a, float* b, float* c, int m, int n)
{
    int commsize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int lb, ub;
    get_chunk(0, m - 1, commsize, rank, &lb, &ub);
    int nrows = ub - lb + 1;
    for (int i = 0; i < nrows; i++) {
        c[lb + i] = 0.0;
        for (int j = 0; j < n; j++)
            c[lb + i] += a[i * n + j] * b[j];
    }

    int* displs = new int[commsize];
    int* rcounts = new int[commsize];
    for (int i = 0; i < commsize; i++) {
        int l, u;
        get_chunk(0, m - 1, commsize, i, &l, &u);
        rcounts[i] = u - l + 1;
        displs[i] = (i > 0) ? displs[i - 1] + rcounts[i - 1] : 0;
    }

    MPI_Allgatherv(&c[lb], ub - lb + 1, MPI_FLOAT, c, rcounts, displs, MPI_FLOAT, MPI_COMM_WORLD);

    free(displs);
    free(rcounts);
}

int main(int argc, char** argv)
{
    int commsize, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double t = MPI_Wtime();

    int lb, ub, m = 280, n = 280;

    get_chunk(0, m - 1, commsize, rank, &lb, &ub);

    int nrows = ub - lb + 1;
    float* a = new float[nrows * n];
    float* b = new float[n];
    float* c = new float[m];

    // Each process initialize their arrays
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < n; j++)
            a[i * n + j] = lb + i + 1;
    }
    for (int j = 0; j < n; j++)
        b[j] = j + 1;
    sgemv(a, b, c, m, n);

    t = MPI_Wtime() - t;

    if (rank == 0) std::cout << t << '\n';

    free(a);
    free(b);
    free(c);

    MPI_Finalize();
}
