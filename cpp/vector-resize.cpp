#include <iostream>
#include <vector>

class A {
public:
  A(bool = true) { std::cout << "Called default constructor\n"; }

  A(const A &) { std::cout << "Called copy constructor\n"; }

  A(A &&) { std::cout << "Called move constructor\n"; }

  A &operator=(const A &) {
    std::cout << "Called copy assignment operator\n";
    return *this;
  }

  A &operator=(A &&) {
    std::cout << "Called move assignment operator\n";
    return *this;
  }
};

int main() {
  std::vector<A> vec;
  A a;
  // vec.resize(1, std::move(a));
  vec.emplace_back(A());
  std::vector<double> b{1, 2, 3, 4, 5};
}
