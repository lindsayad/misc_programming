#include <utility>
#include <iostream>

template <typename T>
struct HasZero
{
  template <typename C>
  static constexpr decltype(std::declval<C>().zero(), bool()) test(int)
  {
    return true;
  }

  template <typename C>
  static constexpr bool test(...)
  {
    return false;
  }

  static constexpr bool value = test<T>(int());
};

template <typename T>
struct A
{
  T data;
  A() : data() {}

  template <typename T2>
  auto my_operator(const T2 & t2, const int & tester, int) -> decltype(tester.zero(), *this);

  template <typename T2>
  A & my_operator(const T2 & t2, const int & tester, ...);
};

template <typename T>
template <typename T2>
inline auto
A<T>::my_operator(const T2 & t2, const int & tester, int) -> decltype(tester.zero(), *this)
{
  std::cout << "I have a zero\n";
  return *this;
}

template <typename T>
template <typename T2>
inline A<T> &
A<T>::my_operator(const T2 & t2, const int & tester, ...)
{
  std::cout << "I dont' have a zero\n";
  return *this;
}

struct B
{
  void zero() const {}
};

int
main()
{
  A<int> a;
  // a.my_operator(5, int());
  // a.my_operator(B(), int());
  // std::cout << HasZero<int>::value << std::endl;
}
