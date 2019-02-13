#include <iostream>
#include <map>

#define getSomeValue this->template get_some_value

template <typename T> class A {
public:
  A() {}

  template <typename T2> void template_method(const T2 &arg) {
    std::cout << arg << std::endl;
  }

  template <typename T2> T2 get_some_value() { return T2(); }
};

template <typename T> class B : public A<T> {
public:
  B() : A<T>() {}

  template <typename T2> void template_method2(const T2 &arg) {
    // std::cout << this->template get_some_value<T2>() << std::endl;
    std::cout << getSomeValue<T2>() << std::endl;
    // this->template_method(arg);
  }
};

int main() {
  B<int> b;
  b.template_method2(5);
}
