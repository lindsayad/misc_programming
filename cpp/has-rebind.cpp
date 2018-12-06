#include <iostream>

template <typename T>
struct hasRebind
{
  template <typename C, typename Enable = typename C::value_type>
  static constexpr bool test(int)
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
  static const bool value = !hasRebind<T>::value;
};

int
main()
{
  std::cout << A<int>::value << std::endl;
}
