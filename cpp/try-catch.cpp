#include <iostream>
#include <stdexcept>

void foo() { throw std::domain_error("You made a mistake you dummy"); }

void bar() {
  try {
    foo();
  } catch (std::runtime_error &) {
    std::cout << "We caught a run-time exception\n";
  }
}

int main() {
  try {
    bar();
  } catch (std::domain_error &) {
    std::cout << "We caught a domain error\n";
  } catch (std::logic_error &) {
    std::cout << "We caught the exception\n";
  }
}
