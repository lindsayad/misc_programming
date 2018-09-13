#include <iostream>

class Apple
{
public:
  Apple() { _x = 1; }
  Apple(int x) { _x = x; }

  void set_x(int /*x*/) const {}
  void set_x(int x) {_x = x;}

  int _x;
};

struct Carrier
{
  Carrier(Apple & apple) : _apple(apple) {}
  void set_apple_x(int x) const
    {
      _apple.set_x(x);
      std::cout << "Const version!\n";
    }
  void set_apple_x(int x)
    {
      _apple.set_x(x);
      _apple = Apple(2000);
      std::cout << "Non-Const version!\n";
    }
  // void set_apple_x(int/* x*/) { std::cout << "Non-const version!\n"; }
  void can_do_it () const {}
  void cant_do_it() {}

private:
  Apple _apple;
};

int main()
{
  Apple apple;
  const Carrier carrier(apple);
  carrier.set_apple_x(7);
  carrier.set_apple_x(5);
  Carrier carrier2(apple);
  carrier2.set_apple_x(7);
  carrier2.can_do_it();
  // carrier.cant_do_it();
  // carrier._apple._x = 5;
}
