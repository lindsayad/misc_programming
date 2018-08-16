class A
{
};

class B
{
protected:
  A a;

protected:
  template <typename T>
  auto method(T arg) -> decltype(a.method(arg));
};

int
main()
{
  B b;
}
