#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank = 0, size = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(
        MPI_COMM_WORLD,
        &rank);

    MPI_Comm_size(
        MPI_COMM_WORLD,
        &size);

    printf("Rank: %d, size: %d\n", rank, size);

    MPI_Finalize();
}
