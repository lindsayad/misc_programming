#include <iostream>
#include <memory>
#include <array>

class B
{
public:
  int data = 5;
  ~B() { std::cout << "B is destructing" << std::endl; }
};

class A
{
public:
  A(const B & foo) : _foo(foo) {}

  void print_foo() { std::cout << _foo.data << std::endl; }

private:
  const B & _foo;
};

std::unique_ptr<A>
makeA()
{
  const B b;
  return std::make_unique<A>(b);
}

std::unique_ptr<A>
makeA2()
{
  return std::make_unique<A>(B{});
}

int
main()
{
  std::unique_ptr<A> a;
  a = makeA();
  a->print_foo();
  a = makeA2();
  a->print_foo();
}
