#include <array>
#include <iostream>

int main() {
  std::array<double, 5> arr{1, 2, 3, 4, 5};

  std::cout << *(arr.end() - 1) << std::endl;
  std::cout << *(arr.end() - 2) << std::endl;
  std::cout << *(arr.end() - 5) << std::endl;
  std::cout << *(arr.rbegin() + 1) << std::endl;
}
