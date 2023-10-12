#include <mpi.h>

#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, num_procs;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  int msg_size = 7;
  MPI_Datatype datatype = MPI_CHAR;

  char* sbuf = new char[msg_size];
  char* rbuf = new char[msg_size * num_procs]();
  std::sprintf(sbuf, "abcdef\n");

  for (int i = 0; i < num_procs; i++) {
    if (i != rank) {
      MPI_Sendrecv(sbuf, msg_size, datatype, i, 0, rbuf + i * msg_size,
                   msg_size, datatype, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }

#if 1
  for (int i = 0; i < num_procs; i++) {
    if (i != rank) {
      std::cout << "Message from process " << i << ":\n" << rbuf << '\n';
    }
  }
#endif

  delete[] sbuf;
  delete[] rbuf;

  MPI_Finalize();
}