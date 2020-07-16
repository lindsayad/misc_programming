#include <iostream>

class MyInt {
public:
  MyInt(int i) : _i(i) {}

  const int &i() const { return _i; }

  operator double() const {
    std::cout << "Calling the conversion operator!\n";
    return 10 * double(this->i());
  }

private:
  int _i;

public:
  int operator()(size_t, size_t) const { return _i; }

  template <typename T> auto operator*(const T &x) const -> decltype(_i * x);
};

template <typename T>
inline auto MyInt::operator*(const T &x) const -> decltype(_i * x) {
  std::cout << "Calling the member operator!" << std::endl;
  (*this)(0, 0);
  return _i * x;
}

double operator*(MyInt &i, double x) {
  std::cout << "Calling the non-member operator with the int as first arg!"
            << std::endl;
  return x * 5 * i.i();
}

// double auto_convert(MyInt &my_int) { return my_int; }

int main() {
  MyInt i(1);
  double x = 2;
  int;
  std::cout << x * i << std::endl;
  std::cout << i * x << std::endl;
  std::cout << i.operator*(x) << std::endl;

  // double y = auto_convert(i);
  // std::cout << y << std::endl;
  // MyInt z(1);
  // double a = z;
}
