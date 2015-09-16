#include <iostream>
#include <cmath>
#include <limits>

int main()
{
  double test = std::numeric_limits<double>::epsilon();
  std::cout << "Test equals " << test << std::endl;
  return 0;
}
