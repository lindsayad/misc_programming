#include <iostream>

class A
{
public:
  int x = 5;
  int y = 7;
  virtual int return_x(int a, int b) { return x; }
  virtual int return_x(int a) { return x; }
};

class B : public A
{
public:
  virtual int return_x(int a, int b) override
    {
      return A::return_x(a);
    }

  using A::return_x;
};

class C : public B
{
public:
  virtual int return_x(int a) override {
    std::cout << y << std::endl;
    std::cout << 32 << std::endl;
    return y;
  }
};

int main()
{
  C c;
  A * a = &c;
  a->return_x(97, 100);


  // int a = 5, c = 7;
  // b.return_x(a, c);
}
