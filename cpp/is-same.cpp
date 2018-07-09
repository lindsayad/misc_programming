#include <type_traits>
#include <iostream>

template <typename T>
class A
{
public:
  bool isInt() { return std::is_same<T, int>::value; }
};

int main()
{
  A<int> a;
  A<double> b;
  std::cout << a.isInt() << std::endl;
  std::cout << b.isInt() << std::endl;
}
