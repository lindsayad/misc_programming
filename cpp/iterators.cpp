#include <iostream>
#include <typeinfo>
#include <vector>

int main() {
  std::vector<int> vec(100);

  auto it = vec.begin();
  auto new_it = it + 10;

  std::cout << typeid(it).name() << std::endl;
  std::cout << typeid(new_it).name() << std::endl;
}
