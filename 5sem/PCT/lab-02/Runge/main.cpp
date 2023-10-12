#include <mpi.h>

#include <cmath>
#include <iostream>

double f(double x) { return (sin(x + 2)) / (0.4 + cos(x)); }

double rectangle_integration(double a, double b, int n) {
  double dx = (b - a) / n;
  double integral = 0.0;
  for (int i = 0; i < n; i++) {
    double x = a + i * dx;
    integral += f(x) * dx;
  }
  return integral;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  double a = -1.0;
  double b = 1.0;
  int n = 1000000;

  // Deduciton
  int local_n = n / size;
  int local_part = local_n * (b - a) / n;
  double local_a = a + rank * local_part;
  double local_b = local_a + local_part;

  // Local integration
  double local_integral = rectangle_integration(local_a, local_b, local_n);

  // Reducing
  double integral;
  MPI_Reduce(&local_integral, &integral, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    std::cout << "Integral: " << integral << std::endl;
  }

  MPI_Finalize();
}
