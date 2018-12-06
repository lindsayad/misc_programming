#include <iostream>

// template <typename T, typename T2>
// void
// f(const T &, T2 &&)
// {
//   std::cout << "Overload1" << std::endl;
// }

// template <typename T, typename T2>
// void
// f(T &&, T2 &&)
// {
//   std::cout << "Overload2" << std::endl;
// }

// template <typename T, typename T2>
// void
// f(T &, T2 &&)
// {
//   std::cout << "Overload3" << std::endl;
// }

// template <typename T, typename T2>
// void
// f(T &)
// {
//   std::cout << "Call reference version." << std::endl;
// }

// template <typename T, typename T2>
// void
// f(const T &&)
// {
//   std::cout << "Call const rvalue reference version." << std::endl;
// }

template <typename T>
void
f(T && arg)
{
  arg = 0;
  std::cout << "Call catch-all." << std::endl;
}

int
main()
{
  int i;
  // f(i);
  // f(1);
  const int j = 0;
  // f(j);
  f(i);
  f(j);
  f(11);
}
