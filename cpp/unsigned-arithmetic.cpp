#include <iostream>
#include <type_traits>

int main() {
  unsigned int i = 2;
  auto j = i - 1;

  std::cout << std::is_same<decltype(j), unsigned int>::value << std::endl;
}
