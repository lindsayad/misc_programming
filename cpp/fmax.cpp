/* fmax example */
//#include <stdio.h>      /* printf */
//#include <math.h>       /* fmax */

int main ()
{
  printf ("fmax (100.0, 1.0) = %f\n", std::max(100.0,1.0));
  printf ("fmax (-100.0, 1.0) = %f\n", std::max(-100.0,1.0));
  printf ("fmax (-100.0, -1.0) = %f\n", std::max(-100.0,-1.0));
  return 0;
}
