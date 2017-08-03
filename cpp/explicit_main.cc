#include "explicit_instantiation.hh"

int main()
{
  Jimmy<std::complex<float>> jimbo;
  std::complex<float> z = jimbo.fp_erf(std::complex<float>(0, 0));
  return 0;
}
