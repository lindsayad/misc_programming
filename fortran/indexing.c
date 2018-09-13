#define NX 3
#define NY 4
#define NZ 5

void print_array_values(const int *values, const int *nvalues);

int
main(int argc, char *argv[])
{
  int index = 0;
  int i,j,k,nvals;

  int values[NX][NY][NZ];
  for(i = 0; i < NX; ++i)
    for(j = 0; j < NY; ++j)
      for(k = 0; k < NZ; ++k)
        values[i][j][k] = index++;

  nvals = NX*NY*NZ;
  print_array_values((const int *)values, &nvals);

  return 0;
}
