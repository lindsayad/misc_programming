#include <iostream>

struct A {
  double data;

  A() : data() {}

  A(double d) : data(d) {}
};

struct AS {
  AS(const A &a) : data(&a.data) { std::cout << "AS conversion constructor\n"; }
  // AS(A &&a) : data(&a.data) { std::cout << "AS move conversion
  // constructor\n"; }

  AS(const AS &as) : data(as.data) { std::cout << "AS copy constructor\n"; }

  double *data;

  AS &operator=(const AS &as) {
    std::cout << "AS copy assignment operator\n";
    *this->data = *as.data;
    return *this;
  }
};

A operator*(const A &a1, const A a2) { return {a1.data * a2.data}; }

int main() {
  A a_to_modify(1);
  AS lhs_surrogate(a_to_modify);

  A a_op1(2);
  A a_op2(3);

  std::cout << a_to_modify.data << std::endl;
  lhs_surrogate = a_op1 * a_op2;
  std::cout << a_to_modify.data << std::endl;
}
