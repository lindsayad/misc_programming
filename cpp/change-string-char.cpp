#include <string>
#include <iostream>

int main()
{
  std::string str = "what";
  char * const pnt = &str[0];
  *pnt = 'c';
  std::cout << str << std::endl;
}
