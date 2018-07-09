#include <string>
#include <vector>
#include <utility>

int main()
{
  std::vector<std::string> v;
  std::string str = "example";
  v.push_back(std::move(str)); // str is now valid but unspecified
  str.back(); // undefined behavior if size() == 0: back() has a precondition !empty()
  str.clear(); // OK, clear() has no preconditions
}
