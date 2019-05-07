class A
{
public:
  typedef double MyDouble;

  MyDouble foo();
};

A::MyDouble
A::foo()
{
  return MyDouble(5);
}

int
main()
{
  A().foo();
}
