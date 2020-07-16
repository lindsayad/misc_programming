#include <cstring>
#include <iostream>

int main()

{
  std::cout << sizeof(std::size_t) << std::endl;
  unsigned int sizes_per_double =
      (sizeof(double) + sizeof(std::size_t) - 1) / sizeof(std::size_t);
  std::cout << sizes_per_double << std::endl;
  std::cout << sizeof(double) << std::endl;

  double one = 1;

  // std::size_t copied[sizes_per_double];
  std::uint64_t copied[sizes_per_double];
  std::uint64_t copied2;
  std::int64_t copied3;

  std::cout << sizeof(copied) << std::endl;

  static_assert(sizeof(std::uint64_t) == sizeof(double),
                "Testing sizes failed");
  static_assert(sizeof(std::int64_t) == sizeof(double), "Testing sizes failed");
  static_assert(sizeof(std::size_t) == sizeof(double), "Testing sizes failed");

  std::memcpy(copied, &one, sizeof(double));
  std::memcpy(&copied2, &one, sizeof(double));
  std::memcpy(&copied3, &one, sizeof(double));

  double dest, dest2, dest3;
  std::memcpy(&dest, copied, sizeof(double));
  std::memcpy(&dest2, &copied2, sizeof(double));
  std::memcpy(&dest3, &copied3, sizeof(double));

  unsigned int ui_zero = 0;

  std::size_t ui_zero_dest;
  std::memcpy(&ui_zero_dest, &ui_zero, sizeof(unsigned int));

  std::cout << "ui_zero_dest is " << ui_zero_dest << std::endl;

  std::memcpy(&ui_zero, &ui_zero_dest, sizeof(unsigned int));

  std::cout << "ui_zero after being copied back is " << ui_zero << std::endl;

  unsigned int ui_one = 1;

  std::size_t ui_one_dest;
  std::memcpy(&ui_one_dest, &ui_one, sizeof(unsigned int));

  std::cout << "ui_one_dest is " << ui_one_dest << std::endl;

  std::memcpy(&ui_one, &ui_one_dest, sizeof(unsigned int));

  std::cout << "ui_one after being copied back is " << ui_one << std::endl;

  std::cout << dest << std::endl;
  std::cout << dest2 << std::endl;
  std::cout << dest3 << std::endl;
  std::cout << one << std::endl;
  std::cout << double(copied[0]) << std::endl;
  std::cout << copied2 << std::endl;
  std::cout << copied3 << std::endl;
}
