#include <sstream>
#include <iostream>

int
main()
{
  std::istringstream ss("xyz_123");
  int64_t id;

  const bool successful_stream = static_cast<bool>(ss >> id);

  std::cout << successful_stream << std::endl;
}
