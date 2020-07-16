#include "metaphysicl/dualdynamicsparsenumberarray.h"

#include <complex>
#include <iostream>
#include <typeinfo>

using namespace MetaPhysicL;
typedef DualNumber<double, DynamicSparseNumberArray<double, unsigned int>>
    DualReal;

int main() {
  DualReal x = 0;
  x.derivatives().insert(0) = 1;

  std::complex<double> y = 0;

  auto z = x * y;
  std::cout << typeid(z).name() << std::endl;
}
