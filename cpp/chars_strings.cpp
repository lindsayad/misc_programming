#include <iostream>
#include <stdlib.h>

int main()
{
  // const char * foo = "hello";
  // std::string bar = foo;
  // std::cout << bar << std::endl;
  char * foo = (char *) malloc(5 * sizeof(char) + 1);
  *foo = 'h';
  *(foo + 1) = 'e';
  *(foo + 2) = 'l';
  *(foo + 3) = 'l';
  *(foo + 4) = 'o';
  *(foo + 5) = '\0';
  std::string nice = foo;
  free (foo);
  std::cout << nice << std::endl;
  // foo = "h";
  // foo = "george";
  // free (foo);
  // free (nice);
}
