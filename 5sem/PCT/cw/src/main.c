#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int get_chunk(int total, int commsize, int rank) {
    int n = total;
    int q = n / commsize;
    if (n % commsize) q++;
    int r = commsize * q - n;
    int chunk = q;
    if (rank >= commsize - r) chunk = q - 1;
    return chunk;
}

int main(int argc, char *argv[]) {
    int n = argc > 1 ? atoi(argv[1]) : 3000;
    int rank, commsize;
    int root = argc > 2 ? atoi(argv[2]) : 0;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    int nrows_current_process = get_chunk(n, commsize, rank);
    // printf("process %d: %d rows\n", rank, nrows_current_process);
    int *rows = malloc(sizeof(*rows) * nrows_current_process);

    double determinant = 1;
    double *a = malloc(sizeof(*a) * nrows_current_process * (n));

    for (int i = 0; i < nrows_current_process; i++) {
        rows[i] = rank + commsize * i;
        srand(rows[i] * n);
        for (int j = 0; j < n; j++) a[i * n + j] = rand() % 2 + 1;
        // printf("Process %d: row %d\n", rank, rows[i]);
    }

    double t = MPI_Wtime();

    double *tmp = malloc(sizeof(*tmp) * (n));
    int row = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i == rows[row]) {
            MPI_Bcast(&a[row * n], n, MPI_DOUBLE, rank, MPI_COMM_WORLD);
            for (int j = 0; j <= n; j++) tmp[j] = a[row * n + j];
            row++;
        } else {
            MPI_Bcast(tmp, n, MPI_DOUBLE, i % commsize, MPI_COMM_WORLD);
        }
        for (int j = row; j < nrows_current_process; j++) {
            double scaling = a[j * n + i] / tmp[i];
            for (int k = i; k < n; k++) a[j * n + k] -= scaling * tmp[k];
        }
    }

    if (rank == root) {
        double locdet = 1;
        int row, j;
        for (j = rank, row = 0; row < nrows_current_process; j += commsize, ++row) {
            determinant = determinant * a[row * n + j];
        }
        for (int i = 0; i < commsize; i++) {
            if (i == root) continue;
            MPI_Recv(&locdet, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            determinant = determinant * locdet;
        }
    } else {
        double locdet = 1;
        int row, j;
        for (j = rank, row = 0; row < nrows_current_process; j += commsize, ++row) {
            locdet = locdet * a[row * n + j];
        }
        MPI_Send(&locdet, 1, MPI_DOUBLE, root, 0, MPI_COMM_WORLD);
    }

    t = MPI_Wtime() - t;

    free(tmp);
    free(rows);
    free(a);

    if (rank == root) {
        printf("Gaussian Determimant(MPI) : n %d, procs %d, time (sec) %.6f\n", n, commsize, t);
    }

    MPI_Finalize();
}