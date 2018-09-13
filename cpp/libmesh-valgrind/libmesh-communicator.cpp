#include <mpi.h>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int i = world_rank;
  MPI_Allreduce(MPI_IN_PLACE, &i, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);

  if (world_rank == 0)
    std::cout << i << std::endl;

  MPI_Finalize();

  return 0;
}
