#include <omp.h>
#include <stdio.h>

int
main()
{
  printf("OpenMP _OPENMP macro: %d\n", _OPENMP);
#ifdef OMP_DISPLAY_ENV
  // OpenMP 5.0+ has environment reporting
#endif
  return 0;
}
