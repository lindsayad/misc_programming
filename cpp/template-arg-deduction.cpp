#include <vector>

template <typename T> void foo(const std::vector<T> &) {}

int main() {
  std::vector<double> arg;
  foo(arg);
}
