#include <memory>
#include <string>
#include <iostream>
#include <set>

class A
{
public:
  std::unique_ptr<int> i;
};

int main()
{
  std::unique_ptr<std::string> unique = std::unique_ptr<std::string>(new std::string("test"));
  std::shared_ptr<std::string> shared = std::move(unique);

  A a;
  a.i = std::unique_ptr<int>(new int(5));
  std::cout << *a.i << std::endl;
  std::shared_ptr<int> b = std::move(a.i);
  std::cout << *b << std::endl;
  // std::cout << *a.i << std::endl; // Segmentation fault!

  std::shared_ptr<std::set<int>> tom = std::make_shared<std::set<int>>();
}
