#include <iostream>

double raw_value(const double &in) { return in; }

int main() {
  const double *ptr;

  double a = 5;

  // no worky
  // ptr = &raw_value(a);

  const double &worky = raw_value(a);
  double &joey = raw_value(a);

  std::cout << *ptr << std::endl;
}
