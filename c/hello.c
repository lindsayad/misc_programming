#include <stdio.h>

#define __ERR(Ln_error) \
  { \
    goto Ln_error; \
  }

int main()
{
  int i = 1;
  /* if (i  == 1) printf("hello world\n"); */
  if (i == 1) __ERR(__pyx_L1_error)
                __pyx_L1_error:;
  printf("hello world\n");
}
