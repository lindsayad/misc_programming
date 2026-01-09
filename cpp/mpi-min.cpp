#include <mpi.h>
#include <limits>
#include <iostream>

int
main(int argc, char ** argv)
{
  int rank;
  unsigned long id;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 2)
    id = 0;
  else
    id = std::numeric_limits<unsigned long>::max();

  MPI_Allreduce_c(MPI_IN_PLACE, &id, 1, MPI_UNSIGNED_LONG, MPI_MIN, MPI_COMM_WORLD);
  std::cout << "On rank " << rank << " the value of id is " << id << std::endl;

  MPI_Finalize();

  return 0;
}
