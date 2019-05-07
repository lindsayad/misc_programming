#include <complex>
#include <cmath>
#include <iostream>

int
main()
{
  std::complex<double> c;
  c = std::numeric_limits<double>::quiet_NaN();
  c.imag(std::numeric_limits<double>::quiet_NaN());
  bool is_nan = std::isnan(c.real());
  is_nan = std::isnan(c.imag());

  std::complex<double> zero = 0;
  std::cout << (zero == std::complex<double>(0)) << std::endl;

  auto new_complex = std::complex<double>(0);
}
