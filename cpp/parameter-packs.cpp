template <template <class...> class OtherTemplate, class... Args> class A {
public:
  OtherTemplate<Args...> member;

  A() {}
  A(const A<OtherTemplate, Args...> &a) = default;
};

template <class... Args> class B {};

template <class... Args, typename T> void foo(B<Args...> &, T &) {}

int main() {
  A<B, int, int, int> a1;

  A<B, int, int, int> a2(a1);

  B<int, int, int> b;
  int num = 5;
  foo(b, num);
}
