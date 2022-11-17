#include <iostream>

// template <typename X>
// struct Test
// {
// }; // to simulate type dependency

// struct X // class declaration: only generic
// {
//   template <typename T>
//   static void f(Test<T>);
// };

// // template definition:
// template <typename T>
// void X::f(Test<T>)
// {
//   std::cout << "generic" << std::endl;
// }
// template <>
// void X::f<void>(Test<void>)
// {
//   std::cout << "specific" << std::endl;
// }

typedef double Real;

class A
{
  template <typename T>
  static std::string f(const T & value);
  template <>
  std::string f(const std::vector<Real> & value);
}

template <typename T>
std::string
A::f(const T &)
{
  std::cout << "generic\n";
  return "";
}

template <>
inline std::string
A::f(const std::vector<Real> &)
{
  std::cout << "specific\n";
  return "";
}

int
main()
{
  A::f(int());
  A::f(std::vector<Real>{});
  // Test<int> ti;
  // Test<void> tv;
  // X::f(ti); // prints 'generic'
  // X::f(tv); // prints 'specific'
}
