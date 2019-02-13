#include "metaphysicl/dualnumberarray.h"
#include <iostream>

using namespace MetaPhysicL;

int main() {

  // DualNumber takes two typename template arguments. The first template
  // argument specifies the type yielded by DualNumber<>::value(). The second
  // template argument specifies the type yielded by
  // DualNumber<>::derivatives(). If the second template argument is not
  // provided, then it defaults to the type of the first, e.g we assume that the
  // derivative and value type are the same. As a first demonstration of second
  // derivative capability we will consider a single variable system. To do
  // second derivatives, the only real clever bit is that we nest DualNumbers:

  DualNumber<DualNumber<double>> x = 5;

  // Unfortunately, calculation of first derivatives is currently redundant so
  // we also have to redundantly seed them
  x.derivatives().value() = 1;
  x.value().derivatives() = 1;

  auto x2 = x * x;
  std::cout << "second derivative is " << x2.derivatives().derivatives()
            << std::endl;
  std::cout << "first derivative is " << x2.derivatives().value() << std::endl;
  std::cout << "first derivative again is " << x2.value().derivatives()
            << std::endl;
  std::cout << "function value is " << x2.value().value() << std::endl;

  // Now we'll consider a multi-variate system. The typing here probably looks
  // terrifying. We want foo.value().value() to be a single scalar, while we
  // want foo.value().derivatives(), foo.derivatives().value(), and
  // foo.derivatives().derivatives() to all yield NumberArrays. With the below
  // typing, foo.value() yields a type of DualNumber<double, NumberArray<2,
  // double>>, and so consequently, foo.value().value() will yield a double and
  // foo.value().derivatives() will yield a NumberArray<2, double> so that's
  // what we need! foo.derivatives() yields a type of DualNumber<NumberArray<2,
  // double>, NumberArray<2, double>> so foo.derivatives().value() and
  // foo.derivatives().derivatives() will both yield NumberArrays like we want

  // Construct "x" variable
  DualNumber<DualNumber<double, NumberArray<2, double>>,
             DualNumber<NumberArray<2, double>, NumberArray<2, double>>>
      xn = 2;

  // Here we seed the zeroth component of the first derivatives vector for our
  // "x" variable
  xn.derivatives().value()[0] = 1.;
  xn.value().derivatives()[0] = 1.;

  // Construct "y" variable
  DualNumber<DualNumber<double, NumberArray<2, double>>,
             DualNumber<NumberArray<2, double>, NumberArray<2, double>>>
      yn = 3;

  // Here we seed the first component of the first derivatives vector for our
  // "y" variable
  yn.derivatives().value()[1] = 1.;
  yn.value().derivatives()[1] = 1.;

  auto x2y3 = xn * xn * yn * yn * yn;
  std::cout << "second derivatives are " << x2y3.derivatives().derivatives()
            << std::endl;
  std::cout << "first derivatives are " << x2y3.derivatives().value()
            << std::endl;
  std::cout << "first derivatives again are " << x2y3.value().derivatives()
            << std::endl;
  std::cout << "function value is " << x2y3.value().value() << std::endl;
}
