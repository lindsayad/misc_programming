#include <vector>

class A
{
  std::vector<A> _list;
};

double
f(const std::vector<double> & input)
{
  double rv = 0;
  for (auto & element : input)
    rv += element;
  return rv;
}

int
main()
{
  A a;
  std::vector<double> input{1, 2, 3, 4, 5};
  auto rv = f(input);
}
