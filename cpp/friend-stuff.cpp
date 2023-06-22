class A
{
  void foo() {}
  A() {}
  friend class B;
  friend class C;
};

class B
{
public:
  A bar() { return {}; }
};

class C
{
public:
  A baz() { return {}; }
};

int
main()
{
}
