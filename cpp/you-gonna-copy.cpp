#include <iostream>

class A
{
public:
  void foo() {}

private:
  A() { std::cout << "Invoked default constructor\n"; }
  A(const A &) { std::cout << "Invoked copy constructor\n"; }
  friend class B;
};

class C
{
public:
  void foo(A a)
  {
    a.foo();
    A copy(a);
  }
};

class B
{
public:
  void foo()
  {
    A a;
    C c;
    c.foo(a);
  }
};

int
main()
{
  B b;
  b.foo();
}
