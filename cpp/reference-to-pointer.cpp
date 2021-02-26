#include <iostream>

class Elem
{
  int * _the_node = nullptr;

public:
  int * & set_node()
    {
      return _the_node;
    }

  void print_node() const
    {
      if (_the_node)
        std::cout << *_the_node << std::endl;
      else
        std::cout << "you're dumb" << std::endl;
    }
};

int main()
{
  Elem the_elem;
  int a = 5;
  int b = 6;
  {
    int * node_a = &a;
    the_elem.set_node() = node_a;
    int * const node_b = &b;
    node_a = node_b;
  }
  the_elem.print_node();
}
