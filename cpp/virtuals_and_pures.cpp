#include <iostream>

class A
{
public:
  virtual void initialize() = 0;
};

class B : A
{
};

class C : B
{
public:
  virtual void initialize()
    {
      _a = 1;
    }
public:
  int _a;
};

int main()
{
  C c;
  c.initialize();
  std::cout << c._a << std::endl;
}
