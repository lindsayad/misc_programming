#include <vector>

template <typename T, typename U>
auto newType(T a, U b) -> std::vector<decltype(a * b)> {
  return std::vector<decltype(a * b)>{a * b};
}

int main() {
  int a = 5, b = 3;
  newType(a, b);
  typedef decltype(a * b) ResultType;
  ResultType c;
  auto e(5);
}
