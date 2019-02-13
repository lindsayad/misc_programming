#include "boost/call_traits.hpp"
#include <iostream>
#include <type_traits>

class A {};

template <typename T,
          typename std::enable_if<
              std::is_same<const T,
                           typename boost::call_traits<T>::param_type>::value,
              int>::type = 0>
void f(const T) {
  std::cout << "Called built-in\n";
}

template <typename T,
          typename std::enable_if<
              std::is_same<const T &,
                           typename boost::call_traits<T>::param_type>::value,
              int>::type = 0>
void f(const T &) {
  std::cout << "Called user type\n";
}

int main() {
  A a;
  int b;
  f(a);
  f(b);
}
