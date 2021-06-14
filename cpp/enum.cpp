#include <iostream>

enum class Normalization { ORTHONORMAL, SQRT_MU, STANDARD };

// template <int N>
// void foo(int N);

int main() {
  enum SomeEnum : int { V1 = 0, V2 = 1, V3 = 2 };
  // SomeEnum a = 0; // compile error
  SomeEnum b;
  std::cout << b << std::endl;
  b = V1;
  b = static_cast<SomeEnum>(1);
  std::cout << b << std::endl;
  b = static_cast<SomeEnum>(4);
  std::cout << b << std::endl;

  // Normalization b = ORTHONORMAL;
  // int b = 5;

  // foo(b);
}
