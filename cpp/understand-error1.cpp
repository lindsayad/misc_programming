#include <type_traits>
#include <iostream>

template <typename T>
class A
{
};

template <typename T>
class B : public A<T>
{
};

template <typename T>
struct BadInstance
{
  typedef typename T::type type;
};

struct Generic
{
};

// template <typename T, class U = typename BadInstance<T>::type>
template <typename T>
void
base(const A<T> &)
{
  typedef typename BadInstance<T>::type U;
  std::cout << "Called the base\n";
}

template <typename T>
void
base(const B<T> &)
{
  std::cout << "Called the derived\n";
}

int
main()
{
  B<Generic> b;
  base(b);
}
