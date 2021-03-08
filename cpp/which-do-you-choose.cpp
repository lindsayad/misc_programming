#include <iostream>

template <typename T>
class A
{};

template <typename T>
class B : public A<T>
{};

template <typename T>
void foo(const T &, void * = nullptr)
{
  std::cout << "Template chosen." << std::endl;
}

template <typename T>
void foo(const A<T> &)
{
  std::cout << "base chosen." << std::endl;
}

int main()
{
  B<double> b;
  foo(b);
}
