#include <iostream>

class A {
protected:
  int _i = 5;
};

class B : public A {
public:
  void print() { std::cout << _i << std::endl; }
};

int main() {
  B b;
  b.print();
}
