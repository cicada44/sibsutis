#include <cmath>
#include <cstdlib>
#include <iostream>
#include <mpi.h>

double f(const double x, const double y)
{
    return x / (y * y);
}

double getrand()
{
    return (double)rand() / RAND_MAX;
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);
    int rank, commsize;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &commsize);

    srand(rank);

    double start_time = MPI_Wtime();

    int in = 0;
    double s = 0;
    int n = 10000000;
    for (int i = rank; i < n; i += commsize) {
        double x = getrand();         /* x in [0, 1] */
        double y = 2 + getrand() * 3; /* y in [2, 5] */
        s += f(x, y);
        ++in;
    }

    double end_time = MPI_Wtime();

    int total_in, total_n;
    MPI_Reduce(&in, &total_in, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&n, &total_n, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double elapsed_time = end_time - start_time;
    double max_elapsed_time;

    MPI_Reduce(&elapsed_time, &max_elapsed_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double result = (double)total_in / total_n;
        std::cout << max_elapsed_time << '\n';
    }

    MPI_Finalize();
}
