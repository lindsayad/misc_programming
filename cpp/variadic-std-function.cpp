#include <functional>

template <typename R, typename... A> void test(R f(A...)) {
  test(std::function<R(A...)>(f));
}

template <typename T, typename T2>
auto do_things(const T &t1, const T2 &t2) -> decltype(t1 * t2) {
  return t1 * t2;
}

int main() {
  double a1;
  double a2;
  test(do_things(a1, a2));
}
