#include <iostream>

class MyInt {
public:
  MyInt(int i) : _i(i) {}

  // double operator*(double x) {
  //   std::cout << "Calling the member operator!" << std::endl;
  //   return x * 5 * this->i();
  // }

  const int &i() const { return _i; }

  operator double() const {
    std::cout << "Calling the conversion operator!\n";
    return 10 * double(this->i());
  }

private:
  int _i;
};

// double operator*(double x, const MyInt &i) {
//   std::cout << "Calling the non-member operator with the double as first
//   arg!"
//             << std::endl;
//   return x * 5 * i.i();
// }
double operator*(MyInt &i, double x) {
  std::cout << "Calling the non-member operator with the int as first arg!"
            << std::endl;
  return x * 5 * i.i();
}

// double auto_convert(MyInt &my_int) { return my_int; }

int main() {
  MyInt i(1);
  double x = 2;
  std::cout << x * i << std::endl;
  std::cout << i * x << std::endl;

  // double y = auto_convert(i);
  // std::cout << y << std::endl;
  // MyInt z(1);
  // double a = z;
}
