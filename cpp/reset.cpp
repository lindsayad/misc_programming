#include <iostream>

template <typename T>
struct hasReset
{
  // We test if the type has reset using decltype and declval.
  template <typename C>
  static constexpr decltype(std::declval<C>().reset(), bool()) test(int /* unused */)
  {
    // We can return values, thanks to constexpr instead of playing with sizeof.
    return true;
  }

  template <typename C>
  static constexpr bool test(...)
  {
    return false;
  }

  // int is used to give the precedence!
  static constexpr bool value = test<T>(int());
};

template <class T>
typename std::enable_if<hasReset<T>::value>::type
reset(T & obj)
{
  obj.reset();
}

template <class T>
typename std::enable_if<!hasReset<T>::value>::type
reset(T & obj)
{
}

struct A
{
  void reset() { std::cout << "I got called to reset!\n"; }
};

struct B
{
};

int
main()
{
  A a;
  B b;
  reset(a);
  reset(b);
}
