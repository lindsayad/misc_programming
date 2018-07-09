#include <set>
#include <iostream>

int main()
{
  std::set<int> set1 = {1, 2, 3, 4, 5};
  std::set<int> set2 = {3, 4, 5};
  std::set<int> set3 = {1, 2, 3};
  std::set<int> set4 = {};

  if (std::includes(set1.begin(), set1.end(), set2.begin(), set2.end()))
    std::cout << "set1 contains set2" << std::endl;

  if (std::includes(set1.begin(), set1.end(), set3.begin(), set3.end()))
    std::cout << "set1 contains set3" << std::endl;

  if (std::includes(set1.begin(), set1.end(), set4.begin(), set4.end()))
    std::cout << "set1 contains set4" << std::endl;

  if (std::includes(set2.begin(), set2.end(), set3.begin(), set3.end()))
    std::cout << "set2 contains set3" << std::endl;
  else
    std::cout << "set2 does not contain set3" << std::endl;
}
