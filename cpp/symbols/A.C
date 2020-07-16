#include "A.h"

template <typename T> void A<T>::validParams() {}

auto foo() -> decltype(A<int>::validParams()) { A<int>::validParams(); }
