#include <iostream>

class A {
public:
  A() {}

  int x = 5;
} a;

int main() { std::cout << a.x << std::endl; }
