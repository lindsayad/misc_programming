#include <iostream>

template <typename T> class A {
public:
  void foo() {}
  void bar();
};

template class A<double>;

int main() {
  A<double> a;
  a.foo();
  A<int> a2;
  a2.foo();
  a2.bar();
}
