#include "metaphysicl/dualnumber.h"

#include <iostream>

using namespace MetaPhysicL;

class B;

class A
{
public:
  A() { std::cout << "Default A constructor\n"; }
  A(int) { std::cout << "called A\n"; }

  A & operator=(const A &)
  {
    std::cout << "Called A assignment\n";
    return *this;
  }
  A & operator=(const B &)
  {
    std::cout << "Called B assignment\n";
    return *this;
  }
};

class B : public A
{
public:
  B(int) : A() { std::cout << "called B\n"; }
};

int
main()
{
  A a;

  DualNumber<double> dn;
  dn = 1;
}
