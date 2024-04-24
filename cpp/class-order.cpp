#include <iostream>

class A
{
public:
  void foo() { std::cout << x << std::endl; }

private:
  int x = 0;
};

int
main()
{
  A a;
  a.foo();
}
