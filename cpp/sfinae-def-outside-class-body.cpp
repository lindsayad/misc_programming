#include <iostream>
#include <type_traits>

template <typename T> class A {
public:
  template <
      typename T2 = T,
      typename std::enable_if<std::is_same<T2, double>::value, int>::type = 0>
  void foo();

  template <
      typename T2 = T,
      typename std::enable_if<!std::is_same<T2, double>::value, int>::type = 0>
  void foo();
};

template <typename T>
template <typename T2,
          typename std::enable_if<std::is_same<T2, double>::value, int>::type>
void A<T>::foo() {
  std::cout << "double overload\n";
}

template <typename T>
template <typename T2,
          typename std::enable_if<!std::is_same<T2, double>::value, int>::type>
void A<T>::foo() {
  std::cout << "generic overload\n";
}

int main() {
  A<double> adouble;
  adouble.foo();
  A<int> aint;
  aint.foo();
}
