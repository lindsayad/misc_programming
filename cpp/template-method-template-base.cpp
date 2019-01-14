template <typename U>
struct B
{
  template <class T>
  void f();
};

template <typename U>
struct D : B<U>
{
  template <typename X>
  using f = typename B<U>::template f<X>;

  void g() { f<int>(); }
};

int
main()
{
  D<int> d;
}
