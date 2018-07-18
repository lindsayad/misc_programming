#include <iostream>

class A
{
public:
  A() : _x(), _y() {}
  int get_x() {return _x;}
  int get_y_val(unsigned index) {return _y[index];}

private:
  int _x;
  int _y[5];
};

template<std::size_t N>
class B
{
public:
  // B() {}
  B() : _data() {}
  int get_data(unsigned index) {return _data[index];}

private:
  int _data[N];
};

int main()
{
  A a;
  int y = a.get_x();
  int z = a.get_y_val(4);
  std::cout << y << std::endl;
  std::cout << z << std::endl;

  B<5> b;
  int zephyr = b.get_data(4);
  std::cout << zephyr << std::endl;
}
