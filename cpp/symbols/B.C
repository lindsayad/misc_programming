#include <B.h>

template <typename T> void B<T>::foo() {}
template <typename T> void B<T>::bar() {}

void baz(B<int> *b) {
  b->foo();
  b->bar();
  // B<int> bnew;
}
