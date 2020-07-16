#include "A.h"

#include <iostream>

// void bar() {
//   A<int> a;
//   a.foo();
// }

template class A<int>;

template <typename T> void A<T>::foo() { std::cout << "Hello" << std::endl; }

// template class A<int>;
