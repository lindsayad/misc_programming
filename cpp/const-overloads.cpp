#include <iostream>

void
foo(int &)
{
  std::cout << "non-const overload" << std::endl;
}

void
foo(const int &)
{
  std::cout << "const overload" << std::endl;
}

int
main()
{
  const int a = 0;
  int b = 0;
  foo(a);
  foo(b);
}
