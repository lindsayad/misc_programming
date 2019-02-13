#include <fenv.h>
#include <iostream>

int main() {
  feenableexcept(FE_DIVBYZERO | FE_INVALID);
  float a = 1, b = 0;
  auto result = a / b;
  std::cout << result << std::endl;
}
