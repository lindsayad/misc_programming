#include <iostream>

class A
{
public:
  A (int);
  int _x;
};

A::A(int x) :
    _x(x)
{}

int main()
{
  int c = 4;
  int b = 2;
  A a(c + b);
  std::cout << a._x << std::endl;
  A & d = a;
  std::cout << d._x << std::endl;
  a._x = 4;
  std::cout << d._x << std::endl;

}
