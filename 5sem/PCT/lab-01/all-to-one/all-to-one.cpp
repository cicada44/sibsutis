#include <mpi.h>

#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
  int rank, num_procs, root = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  size_t size = 10;

  char sbuf[size];
  std::sprintf(sbuf, "Message %d\n", rank);
  char* rbuf = (rank == root) ? new char[size * num_procs] : new char[size];

  if (rank == root) {
    std::memcpy(rbuf, sbuf, size);
    for (int p_num = 1; p_num < num_procs; p_num++) {
      MPI_Recv(rbuf + p_num * size, size, MPI_CHAR, p_num, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
    }
    std::cout << "Process " << rank << " recieved message\n"
              << rbuf << "from all other processes\n";
  } else {
    MPI_Send(sbuf, size, MPI_CHAR, root, 0, MPI_COMM_WORLD);
  }

  delete[] rbuf;

  MPI_Finalize();
}
