/*
  split_type_shared.c

  Build:
    mpicc -O2 -Wall -Wextra -o split_type_shared split_type_shared.c

  Run examples:
    mpirun -n 2 ./split_type_shared
    srun -N 1 -n 2 ./split_type_shared
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void
die_if_mpi_error(int err, const char * where)
{
  if (err == MPI_SUCCESS)
    return;

  char errstr[MPI_MAX_ERROR_STRING];
  int len = 0;
  MPI_Error_string(err, errstr, &len);
  fprintf(stderr, "MPI error at %s: %.*s\n", where, len, errstr);
  MPI_Abort(MPI_COMM_WORLD, 1);
}

int
main(int argc, char ** argv)
{
  int err = MPI_Init(&argc, &argv);
  if (err != MPI_SUCCESS)
  {
    fprintf(stderr, "MPI_Init failed\n");
    return 1;
  }

  int world_rank = -1, world_size = -1;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  char host[MPI_MAX_PROCESSOR_NAME];
  int host_len = 0;
  MPI_Get_processor_name(host, &host_len);

  MPI_Comm local = MPI_COMM_NULL;

  // key = world_rank keeps local ranks ordered by global rank
  err =
      MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, world_rank, MPI_INFO_NULL, &local);
  die_if_mpi_error(err, "MPI_Comm_split_type(MPI_COMM_TYPE_SHARED)");

  int local_rank = -1, local_size = -1;
  if (local != MPI_COMM_NULL)
  {
    MPI_Comm_rank(local, &local_rank);
    MPI_Comm_size(local, &local_size);
  }

  // Serialize output so it doesn't interleave across ranks
  for (int r = 0; r < world_size; ++r)
  {
    if (world_rank == r)
    {
      printf("world %d/%d host=%s pid=%d | local %d/%d\n",
             world_rank,
             world_size,
             host,
             (int)getpid(),
             local_rank,
             local_size);
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  if (local != MPI_COMM_NULL)
  {
    err = MPI_Comm_free(&local);
    die_if_mpi_error(err, "MPI_Comm_free(local)");
  }

  MPI_Finalize();
  return 0;
}
