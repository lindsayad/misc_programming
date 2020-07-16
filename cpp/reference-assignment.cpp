class A
{
  int & _x;

public:
  A(int & x) : _x(x) {}

  // A& operator=(const A & a)
  //   {
  //     _x = a._x;
  //     return *this;
  //   }
  A & operator=(const A &) = default;
};

int main()
{
  int a = 1, b = 2;

  A a1(a);
  A a2(b);

  a1 = a2;
}
