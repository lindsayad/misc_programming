#include <cmath>
#include <iostream>

template <typename T, typename I> class A {
public:
  A(A &&src) = default;
  A(const A &src) = default;
  A() {}

  typedef T value_type;
};

template <typename T, typename I>
auto foo(const A<T, I> &a)
    -> decltype(std::cos(typename A<T, I>::value_type())) {
  return std::cos(typename A<T, I>::value_type());
}

int main() {
  A<int, int> a1;
  A<int, int> a2(a1);
  A<double, double> a3;
  auto result = foo(a3);
  std::cout << result << std::endl;
}
