#include "A.h"
#include <iostream>

// template <>
// void
// A<double>::f()
// {
//   std::cout << "hello2\n";
// }

template <>
A<double>::A()
{
  std::cout << "constructor2\n";
}

template class A<double>;
