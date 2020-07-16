#include <iostream>
#include <vector>

template <typename Iter> void foo(Iter &iter) { iter++; }

int main() {
  std::vector<int> vec = {1, 2};

  auto it = vec.begin();
  std::cout << *it << std::endl;
  foo(it);
  std::cout << *it << std::endl;
}
