#include <vector>
#include <iostream>
#include <utility>

class Elem
{
public:
  Elem(unsigned id) : _id(id) {}

  unsigned id() const { return _id; }

private:
  unsigned _id;
};

int main()
{
  std::vector<Elem *> elems;
  Elem * a = new Elem(0);
  Elem * b = new Elem(1);
  elems.push_back(a);
  elems.push_back(b);

  std::swap(a, b);

  std::cout << elems[0]->id() << std::endl;
  std::cout << elems[1]->id() << std::endl;
  std::cout << a->id() << std::endl;
  std::cout << b->id() << std::endl;

  delete a;
  delete b;
}
