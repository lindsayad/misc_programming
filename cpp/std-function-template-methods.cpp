#include <iostream>
#include <functional>

class A
{
public:
  A() : _x(5), _y(7) {}

  template <typename T>
  const T & foo() const;

private:
  int _x;
  double _y;
};

template <typename T>
const T &
A::foo() const
{
  return _x;
}

template <>
const double &
A::foo<double>() const
{
  return _y;
}

enum ReturnType
{
  Int,
  Double
};

template <typename T>
class B
{
public:
  B(A & a);

  const T & bar();

private:
  std::function<const T &(const A &)> _my_function;

  A & _a;
};

template <typename T>
B<T>::B(A & a) : _a(a)
{
  _my_function = &A::foo<T>;
}

template <typename T>
const T &
B<T>::bar()
{
  return _my_function(_a);
}

int
main()
{
  A a;
  B<int> b1(a);
  B<double> b2(a);

  std::cout << b1.bar() << std::endl;
  std::cout << b2.bar() << std::endl;
}
