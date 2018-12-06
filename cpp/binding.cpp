#include <iostream>

class A
{
public:
  A(int & i) : _data(i), _ptr_data(&i) {}
  A(const A & a) : _data(a.data()), _ptr_data(a._ptr_data) {}

  int & _data;
  int * _ptr_data;

  void modify_this() const { _data = 1000; }
  const int & data() const { return _data; }
  int & data() { return _data; }
};

int
main()
{
  int x = 5;
  A a1(x);
  const A a2(a1);
  int x2 = 9;
  // a2._ptr_data = &x2; // error: cant assign to variable 'a2' with const-qualified type 'const A'
  *a2._ptr_data = x2; // This is fine
  a2._data = x2;      // Somehow this is fine even though a2._data should be a const int &
  std::cout << x << std::endl;
  const int & x3 = x2;
  int x4 = 11;
  // x3 = x4; // error: cannot assign to variable 'x3' with const-qualified type 'const int &'
  a2.modify_this();
  std::cout << x << std::endl;
}
