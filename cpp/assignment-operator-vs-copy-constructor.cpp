#include <iostream>
class A {
public:
  A(const A &) { std::cout << "default constructor\n"; }

  A() { std::cout << "copy constructor\n"; }
};

int main() {
  A a1;
  A a2 = a1;
  a1 = a2;
}
