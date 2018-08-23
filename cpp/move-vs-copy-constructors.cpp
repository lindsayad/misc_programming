#include <iostream>

class A
{
public:
  A() { std::cout << "called default constructor\n"; }
  // A(const A &) { std::cout << "called copy constructor\n"; }
  A(A &&) { std::cout << "called move constructor\n"; }
  A(const A &) = delete;

  // A & operator=(const A &)
  // {
  //   std::cout << "called copy assignment operator\n";
  //   return *this;
  // }
  A & operator=(const A &) = delete;
  A & operator=(A &&)
  {
    std::cout << "called move assignment operator\n";
    return *this;
  }

private:
  int i_;
};

A operator*(const A &, const A &) { return {}; }
// A operator*(const A & a, const A &) { return a; }

int
main()
{
  A a;
  A a2 = a * a;
}
