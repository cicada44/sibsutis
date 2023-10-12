#include <mpi.h>

#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  int msg_size = 6;
  MPI_Datatype datatype = MPI_CHAR;

  char* sbuf = new char[msg_size];
  char* rbuf = new char[msg_size];

  if (rank == 0) {
    std::strcpy(sbuf, "abcdef");
    for (int i = 1; i < num_procs; i++) {
      MPI_Send(sbuf, msg_size, datatype, i, 0, MPI_COMM_WORLD);
    }
    std::cout << "Process " << rank << " sent message to all other processes."
              << std::endl;
  } else {
    MPI_Recv(rbuf, msg_size, datatype, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Process " << rank << " received message: " << rbuf
              << std::endl;
  }

  delete[] sbuf;
  delete[] rbuf;

  MPI_Finalize();
}