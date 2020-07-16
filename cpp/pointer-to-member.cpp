#include <iostream>

class A {
public:
  virtual ~A();
  // void swap() { std::cout << "I am the base\n"; }
  virtual void swap() { std::cout << "I am the base\n"; }
  // virtual void swap() = 0;
};

A::~A() {}

class B : public A {
public:
  void swap() override { std::cout << "I am the derived\n"; }
};

int main() {
  void (A::*aptr)() = &A::swap;
  void (B::*bptr)() = &A::swap;

  B b;
  (b.*bptr)();
  (b.*aptr)();

  A a;
  // (a.*bptr)(); compiler error not surprising
  (a.*aptr)();

  // void (A::*aptr2)() = &B::swap;
  void (B::*bptr2)() = &B::swap;

  // (b.*aptr2)();
  (b.*bptr2)();
}
