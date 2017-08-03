#include <iostream>

int & return_ref(int & x)
{
  int & y = x;
  return y;
}

int main()
{
  int a = 2;
  int & b = a;
  int * c = &a;
  a = 3;
  std::cout << b << std::endl;
  std::cout << *c << std::endl;
  int & y = return_ref(a);
  a = 70;
  std::cout << y << std::endl;
}
