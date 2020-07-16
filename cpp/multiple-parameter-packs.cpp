template <typename T> struct A {};

template <typename T> struct B {};

template <typename... Ts> void one(A<Ts...> a) {}

template <typename... Ts, typename... Us> void two(A<Ts...> a, B<Us...> b) {}

int main() {
  auto a = A<int>();
  auto b = B<int>();

  // Just fine
  // one();
  one(a);
  // one(a, a);

  // All errors
  // two();
  // two(a);
  two(a, b);
}
