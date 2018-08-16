#include <map>

int
main()
{
  std::map<int, int> m;
  m.emplace(5, 7);
  int x = 5;
  m.emplace(7, x);
  // m.emplace(9, {12}); Doesn't compile: deduced incomplete pack <int, (no value)> for template
  // parameter '_Args'
  m.emplace(std::piecewise_construct, std::tuple<int>(12), std::tuple<int>(6));
}
