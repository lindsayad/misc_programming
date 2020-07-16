#include <iostream>
#include <vector>

int main() {
  std::vector<int> x;
  x.reserve(50);
  std::vector<int> y = {1, 2, 3, 4, 5};
  x = y;
  std::cout << x.capacity() << std::endl;
  std::vector<int> z = x;
  std::cout << z.capacity() << std::endl;
  std::cout << z.size() << std::endl;
  std::vector<int> a = std::move(x);
  std::cout << a.capacity() << std::endl;
  std::cout << a.size() << std::endl;
  std::vector<int> b;
  b = std::move(a);
  std::cout << b.capacity() << std::endl;
  std::cout << b.size() << std::endl;
}
