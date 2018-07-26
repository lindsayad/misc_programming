#include <iostream>

void add_number(double & x)
{
  x += 2.;
}

int main()
{
  double y = 5.;
  double * z = &y;
  add_number(*z);
  std::cout << y << std::endl;
}
