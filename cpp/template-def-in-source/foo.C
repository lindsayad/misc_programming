#include "templ.h"
#include <iostream>

template <typename T> void A<T>::foo() { std::cout << "Im Rob flanigan\n"; }

template class A<double>;
template class A<int>;
