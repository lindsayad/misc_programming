#include <iostream>

template <typename T> void foo(const T &) {
  std::cout << "const version called\n";
}

template <typename T> void foo(T &) {
  std::cout << "non-const version called\n";
}

int main() {
  const int a = 5;
  int b = 6;
  foo(a);
  foo(b);
}
