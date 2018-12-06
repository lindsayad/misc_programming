#include "libmesh/communicator.h"
// #include <mpi.h>
#include <unistd.h>
#include <iostream>

class Communicator
{
public:
  Communicator(const MPI_Comm & comm) : _communicator(MPI_COMM_SELF) { assign(comm); }

  void assign(const MPI_Comm & comm)
  {
    _communicator = comm;
    if (_communicator != MPI_COMM_NULL)
    {
      int i;
      MPI_Comm_size(_communicator, &i);

      _size = i;

      MPI_Comm_rank(_communicator, &i);

      _rank = i;
    }
    else
    {
      _rank = 0;
      _size = 1;
    }
  }

private:
  MPI_Comm _communicator;
  int _rank;
  int _size;
};

int
main()
{
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // int i = 0;
  // char hostname[256];
  // gethostname(hostname, sizeof(hostname));
  // printf("PID %d on %s ready for attach\n", getpid(), hostname);
  // fflush(stdout);
  //   while (0 == i)
  //     sleep(5);

  MPI_Comm my_comm(MPI_COMM_WORLD);

  std::cout << my_comm << std::endl;

  // // libMesh::Parallel::Communicator comm;
  libMesh::Parallel::Communicator comm(my_comm);
  // comm.min(i);

  // Communicator comm(my_comm);

  std::cout << my_comm << std::endl;

  // Finalize the MPI environment.
  MPI_Finalize();
}
