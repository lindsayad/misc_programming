#include <iostream>
#include <type_traits>
#include <vector>

int main() {
  std::vector<double> a(100);

  auto type1 = a;
  auto &type2 = a;

  std::cout << std::is_reference<decltype(type1)>::value << std::endl;
  std::cout << std::is_reference<decltype(type2)>::value << std::endl;
}
