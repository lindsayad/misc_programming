#include <algorithm>
#include <typeinfo>
#include <iostream>

int
main()
{
  unsigned short a = 1;
  unsigned int b = 1;
  auto result = a / b;
  auto result2 = b - b;
  std::cout << typeid(decltype(result)).name() << std::endl;
  std::cout << typeid(decltype(a)).name() << std::endl;
  std::cout << typeid(decltype(b)).name() << std::endl;
  std::cout << typeid(decltype(result2)).name() << std::endl;
}
