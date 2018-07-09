#include <iostream>

class A
{
public:
  virtual void print_hello() {}
};

class B : public A
{
public:
  void print_hello() override
    {
      std::cout << "hello" << std::endl;
    }
};

int main()
{
  B b;
  A * a = &b;
  a->print_hello();
}
