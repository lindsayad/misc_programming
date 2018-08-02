#include <iostream>
#include <utility>

class A {
public:
  A() {}

  template <typename T, typename std::enable_if<std::is_same<T, double>::value,
                                                int>::type = 0>
  A operator*=(const T &) {
    std::cout << "Calling template\n";
    return *this;
  }

  A operator*=(const A &) {
    std::cout << "Calling non-template\n";
    return *this;
  }
};

class B : public A {};

struct HasType {
  typedef int type;
};

template <typename T, typename U,
          typename std::enable_if<std::is_same<T, HasType>::value>::type = void>
struct Test {
  static const bool value = false;
};

// template <typename T>
// struct Test<int, T,
//             typename std::enable_if<std::is_same<T, int>::value, void>::type>
//             {
//   static const bool value = true;
// };

int main() {
  B b;
  b *= b;
  // std::cout << Test<double, double>::value << std::endl;
  // std::cout << Test<int, int>::value << std::endl;
  std::cout << Test<HasType, double>::value << std::endl;
}
