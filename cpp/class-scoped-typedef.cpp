#include <iostream>
#include <type_traits>
#include <typeinfo>

class A {
public:
  typedef double MyDouble;

  MyDouble foo();
};

A::MyDouble A::foo() { return MyDouble(5); }

template <typename> class BTempl;

typedef BTempl<double> B;

template <typename T> class BTempl {
public:
  typedef T type;
  typedef BTempl<T> B;
  BTempl() {}
  BTempl(const B &) = default;
  BTempl(B &&) = default;
  B &operator=(const B &) = default;
  B &operator=(B &&) = default;
  ~BTempl() = default;

  const B &foo();
  const B &foo(const B &);
};

template <typename T> const typename BTempl<T>::B &BTempl<T>::foo() {
  std::cout << std::is_same<B, BTempl<T>>::value << std::endl;
  return *this;
}

template <typename T> const typename BTempl<T>::B &BTempl<T>::foo(const B &) {
  std::cout << std::is_same<B, BTempl<T>>::value << std::endl;
  return *this;
}

template <typename T> const BTempl<T> &foo(const BTempl<T> &b) {
  std::cout << std::is_same<B, BTempl<T>>::value << std::endl;
  return b;
}

template <typename T> class CTempl : public BTempl<T> {
public:
  CTempl() : B() {}
};

int main() {
  A().foo();
  BTempl<double> b_double;
  BTempl<int> b_int;
  b_double.foo();
  b_double.foo(b_double);

  // compile error because we expect a type BTempl<double> as an argument
  // b_double.foo(b_int);

  foo(b_double);
  b_int.foo();

  // compile error because we expect a type BTempl<int> as an argument
  // b_int.foo(b_double);

  b_int.foo(b_int);
  foo(b_int);

  CTempl<double> c_double;
}
