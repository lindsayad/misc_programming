// my first program in C++ !!!

#include <iostream>
using namespace std;

#ifndef __GLIBCXX__
#error Not using libstdc++
#endif

// int
// main()
// {
//   int i = 0;
//   for (int j = 0; j < 1000000; ++j)
//     i += j;
//   cout << "Hello World!\nI'm a C++ program\n";
//   //	std::cout << "I'm a C++ program\n";
// }

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
