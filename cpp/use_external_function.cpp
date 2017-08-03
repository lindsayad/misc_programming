#include "Faddeeva.hh"
#include <iostream>

int main()
{
  double answer;
  answer = Faddeeva::erf(0.);
  std::cout << answer << std::endl;
  std::cout << Faddeeva::erf(1.) << std::endl;
  return 0;
}
