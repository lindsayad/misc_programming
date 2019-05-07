#include <utility>

int
main()
{
  std::pair<unsigned, unsigned> key;
  bool flag = true;
  if (flag)
    key = {1, 2};
  else
    key = {2, 1};
}
