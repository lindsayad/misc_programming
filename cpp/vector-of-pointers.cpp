#include <iostream>
#include <vector>

class A {
public:
  void foo() const { std::cout << "Hi there!\n"; }

  void bar() { std::cout << "Hi there!\n"; }
};

int main() {
  std::vector<A *> a(5);

  for (auto *elem : a)
    elem = new A;

  for (const auto *const elem : a) {
    elem->foo();

    // The line below won't compile because we are trying to call a non-const
    // method with a const object

    // elem->bar();
  }

  for (const auto &elem : a) {
    elem->foo();

    // This line compiles fine however, because we are calling through pointer
    // to non-const. Not as safe as we might have thought!
    elem->bar();
  }

  for (auto *elem : a)
    delete elem;
}
