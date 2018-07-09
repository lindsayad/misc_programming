#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

template <typename T>
std::string
implodeString(const T & strings, const char * delim)
{
  std::ostringstream imploded;
  std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(imploded, delim));
  std::string result = imploded.str();
  result.erase(result.rfind(delim));
  return result;
}

int main()
{
  std::vector<std::string> strings = {"one", "two", "three"};

  std::string result = implodeString(strings, "");
  std::cout << result << std::endl;
}
