#include "metaphysicl/dualdynamicsparsenumbervector.h"

using namespace MetaPhysicL;

int main() {

  DynamicSparseNumberVector<double, unsigned int> dsnv;

  // // Compiler error becaus x is not a converted constant expression
  // unsigned int x = 5;
  // dsnv.insert<x>() = 1;

  const unsigned int x = 5;
  dsnv.insert<x>() = 1;

  // // Compiler error because z is not a converted constant expression
  // unsigned int y = 7;
  // const unsigned int z = y;
  // dsnv.insert<z>() = 1;
}
