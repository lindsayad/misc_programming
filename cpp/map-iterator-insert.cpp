#include <map>
#include <utility>

int
main()
{
  std::map<unsigned, unsigned> a;
  unsigned key = 1;
  auto && it = a.find(key);
  a.insert(it, std::make_pair(key, 1));
}
