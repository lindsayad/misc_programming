#include <mpi.h>
#include <stddef.h>

struct foo{
  float value;
  char rank;
};

class A
{
public:
  A() : _datatype() {

    int count = 2;
    int array_of_blocklengths[] = { 1, 1 };
    MPI_Aint array_of_displacements[] = { offsetof(struct foo,value ),
                                          offsetof(struct foo,rank ) };
    MPI_Datatype array_of_types[] = { MPI_FLOAT, MPI_CHAR };
    MPI_Datatype tmp_type;
    MPI_Aint lb, extent;

    MPI_Type_create_struct( count, array_of_blocklengths, array_of_displacements,
                            array_of_types, &tmp_type );
    MPI_Type_commit(&tmp_type);
    MPI_Type_get_extent( tmp_type, &lb, &extent );
    MPI_Type_create_resized( tmp_type, lb, extent, &_datatype );
    MPI_Type_commit( &_datatype );

  }

  ~A() { MPI_Type_free(&_datatype); MPI_Finalize(); }

protected:
  MPI_Datatype _datatype;
};

int main()
{
  MPI_Init(NULL, NULL);
  A * a = new A;
  delete a;
}
