#include <iostream>

class B
{
public:
  B() {}

  void amethod() {}
};

class A
{
public:
  int data;

  void amethod() {}

  A() : data() {}
};

class C : public A, public B
{
public:
  C() : A(), B() {}

  using A::amethod;
};

int
main()
{
  C c;
  c.amethod();
}
