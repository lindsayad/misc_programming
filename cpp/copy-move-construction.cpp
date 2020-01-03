#include <iostream>

class A {
public:
  A(const A &) { std::cout << "copy construct\n"; }

  A(A &&) { std::cout << "copy construct\n"; }

  A() {}
};

// A foo(A &&a) { return a; }

A foo(A a) {
  std::cout << "In one-arg method\n";
  return a;
}

A foo() {
  std::cout << "In zero-arg method\n";
  A a;
  return a;
}

int main() {
  A a1;
  A a2;
  auto a3 = foo(std::move(a1));
  auto a4 = foo(a2);
  auto a5 = foo();
}
