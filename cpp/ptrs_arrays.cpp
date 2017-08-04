#include <iostream>
#include <stdlib.h>

int main()
{
  int j[3];
  int * p = j;
  int * q = p + 1;
  int * r = p + 2;
  *p = 4;
  *q = 5;
  *r = 6;
  std::cout << j[0] << j[1] << j[2] << std::endl;
}
