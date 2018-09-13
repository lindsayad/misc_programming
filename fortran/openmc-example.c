#include <iostream>
#include <cstring>

extern "C" {
  void get(const char *);
};

int main()
{
  char buffer[20];
  get(buffer);
  std::cout << buffer << std::endl;
  std::cout << "length of array is " << strlen(buffer) << std::endl;
}
