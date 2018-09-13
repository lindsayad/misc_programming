#include "mpi.h"
#include <stdio.h>
#include <stddef.h>

struct foo{
  float value;
  char rank;
};

int main()
{
  MPI_Init(NULL, NULL);
  int count = 2;
  int array_of_blocklengths[] = { 1, 1 };
  MPI_Aint array_of_displacements[] = { offsetof(struct foo,value ),
                                        offsetof(struct foo,rank ) };
  MPI_Datatype array_of_types[] = { MPI_FLOAT, MPI_CHAR };
  MPI_Datatype tmp_type, my_mpi_type;
  MPI_Aint lb, extent;

  MPI_Type_create_struct( count, array_of_blocklengths, array_of_displacements,
                          array_of_types, &tmp_type );
  MPI_Type_commit(&tmp_type);
  MPI_Type_get_extent( tmp_type, &lb, &extent );
  MPI_Type_create_resized( tmp_type, lb, extent, &my_mpi_type );
  MPI_Type_commit( &my_mpi_type );
  MPI_Finalize();
}
