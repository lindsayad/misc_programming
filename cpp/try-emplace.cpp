#include <map>
#include <iostream>

int
main()
{
  std::map<int, double> ex;
  ex[0] = 0;

  auto lammy = []()
  {
    std::cout << "I got called\n";
    return 0;
  };

  ex.try_emplace(0, lammy());
}
