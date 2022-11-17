#include <memory>
#include <iostream>

int
main()
{
  std::unique_ptr<int> a, b;
  a = std::make_unique<int>(5);
  std::cout << static_cast<short int>(bool(a)) << std::endl;
  std::cout << static_cast<short int>(bool(b)) << std::endl;
}
