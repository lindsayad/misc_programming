#include <iostream>

#define adGetParam                                                             \
  _Pragma(                                                                     \
      "GCC warning \"adGetParam is deprecated. Simply use getParam\"") this    \
      ->template getParam

class A {
public:
  template <typename T> void getParam() {}
};

class B : public A {
public:
  void foo() { adGetParam<int>(); }
};

int main() {
  B b;
  b.foo();
}
