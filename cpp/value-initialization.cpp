#include <iostream>

class A {
public:
  A() : _x(), _y() {}
  int get_x() { return _x; }
  int get_y_val(unsigned index) { return _y[index]; }

private:
  int _x;
  int _y[5];
};

template <std::size_t N> class B {
public:
  B() {}
  B(bool /*arg*/) : _data() {}
  // B() : _data() {}
  int get_data(unsigned index) { return _data[index]; }

private:
  int _data[N];
};

class C {
public:
  C() = default;
  C(const C &) = default;

  bool do_derivatives = false;
};

int main() {
  A a;
  int y = a.get_x();
  int z = a.get_y_val(4);
  std::cout << y << std::endl;
  std::cout << z << std::endl;

  B<5> b;
  // B<5> b(true);
  int zephyr = b.get_data(4);
  std::cout << zephyr << std::endl;

  C c1;
  C c2{};

  c1.do_derivatives = true;

  C c3(c1);
  std::cout << "Output of do c3 do_derivatives is ";
  std::cout << c3.do_derivatives << std::endl;
  std::cout << "Output of do c2 do_derivatives is ";
  std::cout << c2.do_derivatives << std::endl;
}
