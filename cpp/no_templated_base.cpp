#include <iostream>
#include <vector>

class TheBase
{
public:
  int _x = 5;
};

template <typename T>
class TemplatedChild : public TheBase
{
public:
  TemplatedChild(T x) : _y(x) {}
  T _y;
};


int main()
{
  std::vector<TheBase *> pointers;
  pointers.push_back(new TemplatedChild<int>(1));
  pointers.push_back(new TemplatedChild<float>(2));
  std::cout << pointers[0]->_y << std::endl;
  std::cout << pointers[1]->_y << std::endl;
}
