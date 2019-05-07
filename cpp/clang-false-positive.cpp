class A
{
public:
  A() : _x(5), _y(7), _ptr1(&_x), _ptr2(&_x) {}

  // const int * const & ptr() const { return _ptr2; }
  const int * const & ptr() const { return _ptr1; }
  // int *& ptr() { return _ptr1; }

private:
  int _x, _y;
  int * _ptr1;
  const int * _ptr2;
};

int
main()
{
  A a;
  auto && ptr = a.ptr();
  *ptr = 7;
}
