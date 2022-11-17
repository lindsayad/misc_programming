#include <unordered_map>
#include <iostream>

int
main()
{
  std::unordered_map<int, int> a;
  try
  {
    a.at(1);
  }
  catch (std::out_of_range & e)
  {
    std::cout << e.what() << std::endl;
  }
}
