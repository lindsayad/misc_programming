#include <iostream>

int
fib(int n)
{
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int
main()
{
  const auto res = fib(42);
  std::cout << res << std::endl;
}
