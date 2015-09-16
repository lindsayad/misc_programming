#include <stdio.h>
#include <math.h>
#include <errno.h>

int main(void)
{
    double param, result;

    errno = 0;
    param = 100;
    result = exp (param);
    if (errno == ERANGE) {
        printf("exp(%f) overflows\n", param);
        result = param;
    }
    else 
      printf ("The exponential value of %f is %f.\n", param, result );
    return 0;
}
