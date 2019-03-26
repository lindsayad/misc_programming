#include <cerrno>
#include <cfenv>
#include <cmath>
#include <cstring>
#include <iostream>
#pragma STDC FENV_ACCESS ON

int main() {
  std::cout << "MATH_ERRNO is "
            << (math_errhandling & MATH_ERRNO ? "set" : "not set") << '\n'
            << "MATH_ERREXCEPT is "
            << (math_errhandling & MATH_ERREXCEPT ? "set" : "not set") << '\n';
  std::feclearexcept(FE_ALL_EXCEPT);
  errno = 0;

  auto val = std::pow(-1.67, 0.18);
  std::cout << val << std::endl;

  if (errno == EDOM)
    std::cout << "errno = EDOM (" << std::strerror(errno) << ")\n";

  if (errno == ERANGE)
    std::cout << "errno = ERANGE (" << std::strerror(errno) << ")\n";
}
