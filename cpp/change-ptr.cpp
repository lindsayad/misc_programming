class A
{
public:
  void changePointerLocation(const int & x) const { p = &x; }

private:
  mutable const int * p;
};

int
main()
{
  A a;
  int b = 5;
  a.changePointerLocation(b);
}
