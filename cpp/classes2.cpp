#include <iostream>                            
                                               
struct B
{
public:
  int _x = 5;
};

class A
{
public:
  A(int x) : _x(x) {}
  A() : _x(1) {}

  int _x;

  B b;
};


int main()
{
  A a;
  std::cout << a.b._x << std::endl;
}

  
