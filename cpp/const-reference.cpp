#include <iostream>

class A
{
public:
  A()
    {
      _x = 1.;
    }

  const double & get() const
    {
      std::cout << "Calling the read-only getter." << std::endl;
      return _x;
    }

  double & get()
    {
      std::cout << "Calling the writeable getter." << std::endl;
      return _x;
    }
private:
  double _x;
};

int main()
{
  A a;
  double & x = a.get();
  const double & y = a.get();
  const A b;
  double & z = b.get();
  const double & w = b.get();
}
