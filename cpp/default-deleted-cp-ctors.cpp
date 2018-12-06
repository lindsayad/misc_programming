struct A
{
  A(A &) = default;
  A(const A &) = delete;
  A() {}
};

struct B : A
{
  B(const B &) = default;
  B() {}
};

int
main()
{
  B b;
}
