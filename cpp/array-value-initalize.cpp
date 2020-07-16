#include <iostream>

template <typename T> T *foo(T, unsigned int size) { return new T[size](); }

int main() {
  double *bar = foo(double(0), 2);

  std::cout << bar[0];

  delete[] bar;
}
