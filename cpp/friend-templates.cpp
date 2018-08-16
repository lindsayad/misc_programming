#include <iostream>

template <typename T>
class Foo; // pre-declare the template class itself
template <typename T>
Foo<T> operator+(const Foo<T> & lhs, const Foo<T> & rhs);
template <typename T>
std::ostream & operator<<(std::ostream & o, const Foo<T> & x);

template <typename T>
class Foo
{
public:
  Foo(const T & value = T());
  friend Foo<T> operator+<>(const Foo<T> & lhs, const Foo<T> & rhs);
  friend std::ostream & operator<<<>(std::ostream & o, const Foo<T> & x);

private:
  T value_;
};

template <typename T>
Foo<T>::Foo(const T & value) : value_(value)
{
}
template <typename T>
Foo<T>
operator+(const Foo<T> & lhs, const Foo<T> & rhs)
{
  return Foo<T>(lhs.value_ + rhs.value_);
}
template <typename T>
std::ostream &
operator<<(std::ostream & o, const Foo<T> & x)
{
  return o << x.value_;
}

int
main()
{
  Foo<int> lhs(1);
  Foo<int> rhs(2);
  Foo<int> result = lhs + rhs;
  std::cout << result << std::endl;
  ;
}
