#include <iostream>

template <typename T, typename V> struct A {
  template <typename U> void foo(const U &);
};

template <typename V> template <typename U> void A<int, V>::foo(const U &) {
  std::cout << "I'm an int\n";
}

template <typename T, typename V>
template <typename U>
void A<T, V>::foo(const U &) {
  std::cout << "I'm general\n";
}

int main() {
  A<int, int> a;
  A<double, int> b;

  a.foo(5);

  b.foo(5);
}
