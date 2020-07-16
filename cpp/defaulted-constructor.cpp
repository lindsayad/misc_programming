#include <iostream>

class A {
public:
  A(const A &) { std::cout << "Calling base copy constructor\n"; }
  A() { std::cout << "Calling base default constructor\n"; }
};

class B : public A {
public:
  B(const B &) = default;
  B() {}
};

int main() {
  B b1;
  B b2(b1);
}
