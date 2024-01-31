#include <iostream>
#include <memory>

class A
{
public:
  A(const int & foo) : _foo(foo) {}

  void print_foo() { std::cout << _foo << std::endl; }

private:
  const int & _foo;
};

int
main()
{
  std::unique_ptr<A> a;
  {
    const int i = 5;
    a = std::make_unique<A>(i);
  }
  a->print_foo();
}
