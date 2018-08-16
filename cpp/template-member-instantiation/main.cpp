#include "A.h"
#include "B.h"
#include "C.h"

int
main()
{
  A a;
  a.ptr = new B();
  // a.method<int>();
  return 0;
}
