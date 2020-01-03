#include <iostream>

class A {
public:
  A &operator=(const A &) {
    std::cout << "A assignment\n";
    return *this;
  }
};

class B : public A {
public:
  B &operator=(const B &) {
    std::cout << "B assignment\n";
    return *this;
  }

  B &operator=(const A &) {
    std::cout << "Tricky B assignment\n";
    return *this;
  }
};

int main() {
  A *one = new (B);
  A *two = new (B);

  *one = *two;

  delete one;
  delete two;
}
