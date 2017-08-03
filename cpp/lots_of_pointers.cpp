#include <iostream>
#include <stdlib.h>

int main()
{
  // int a = 1;
  // int *b = &a;
  int *b = (int *) malloc(sizeof(int));
  *b = 5;
  int *c = b;
  int *d = c;
  free (d);
  // *b = 7;
  std::cout << *b << std::endl;
}
