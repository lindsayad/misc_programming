#include <type_traits>
#include <iostream>

template <class T>
constexpr std::false_type
always_false()
{
}

int
main()
{
  decltype(always_false<int>()) a;
  bool b;
  std::cout << typeid(a).name() << std::endl;
  std::cout << typeid(b).name() << std::endl;
  std::cout << always_false<int>() << std::endl;
}
