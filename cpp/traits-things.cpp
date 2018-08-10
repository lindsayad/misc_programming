#include <cstdlib>

template <typename T, std::size_t N> struct NumberArray {
  NumberArray() : _data() {}

  T _data[N];
};

template <typename T, typename U> struct A {
  A() {}
};

template <typename T, std::size_t N> struct B : public A<T, NumberArray<T, N>> {
  B() : A<T, NumberArray<T, N>>() {}
  void row(const NumberArray<T, N> &) {}
};

int main() { B<double, 10> b; }
