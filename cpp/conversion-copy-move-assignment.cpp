#include <iostream>
#include <map>
#include <type_traits>
#include <utility>

template <typename T> class A {
public:
  A() : _data() { std::cout << "Default constructor is being called\n"; }

  A(const T &in) : _data(in) {
    std::cout << "Single argument conversion constructor is being called\n";
  }

  A(const A<T> &a) : _data(a._data) {
    std::cout << "Copy constructor being called\n";
  }

  A(const A<T> &&a) : _data(a._data) {
    std::cout << "Move constructor being called\n";
  }

  template <typename U,
            typename std::enable_if<!std::is_same<T, U>::value, int>::type = 0>
  A(A<U> &a) : _data(&a._data) {
    std::cout << "Single A conversion constructor being called\n";
  }

  A<T> &operator=(const A<T> &a) {
    _data = a._data;
    std::cout << "Copy assignment operator being called\n";
    return *this;
  }

  T _data;
};

template <typename T> class MyDouble;
template <typename T> class Base;

class MyInt {
public:
  MyInt(int x) : _x(x) { std::cout << "Calling int conversion constructor\n"; }

  MyInt(const MyInt &my_int) : _x(my_int._x) {
    std::cout << "Calling copy constructor\n";
  }

  MyInt(const double &d) : _x(d) {}

  MyInt &operator=(const MyInt &my_int) {
    std::cout << "Calling copy assignment operator\n";
    _x = my_int._x;
    return *this;
  }

  MyInt() : _x() {}

  MyInt(const MyDouble<MyInt> &d);

  MyInt(const Base<MyInt> &d);

private:
  int _x;
};

template <typename T> class Base {
public:
  Base(double x) : _x(x) {
    std::cout << "Calling double conversion constructor\n";
  }

  operator T() {
    std::cout << "Calling templated conversion operator\n";
    return _my_int;
  }

  const double &x() const { return _x; }

protected:
  double _x;
  MyInt _my_int;
};

template <typename T> class MyDouble : public Base<T> {
public:
  using Base<T>::Base;

  operator MyInt() {
    std::cout << "Calling non-const operator MyInt conversion\n";
    return this->_my_int;
  }

  operator MyInt() const {
    std::cout << "Calling const operator MyInt conversion\n";
    return this->_my_int;
  }

  operator double() const { return this->_x; }
};

MyInt::MyInt(const MyDouble<MyInt> &d) : _x(d.x()) {}

MyInt::MyInt(const Base<MyInt> &d) : _x(d.x()) {}

int main() {
  std::map<unsigned, A<double>> m;
  m[0] = A<double>{2};
  m[1] = {2};

  A<double> a;
  A<double *> ref(a);
  A<double> copya(a);
  A<double> movea(std::move(copya));

  std::cout << a._data << std::endl;
  *ref._data = 5;
  std::cout << a._data << std::endl;
  std::cout << std::is_same<decltype(a), decltype(ref)>::value << std::endl;

  int d = 0;
  int &b = d;
  int c = 1;
  b = c;
  const int &e = d;
  int f = e;

  A<double> a2;
  ref = a2;
  std::cout << "a data before is " << a._data << std::endl;
  std::cout << "a2 data before is " << a2._data << std::endl;
  *ref._data = 10;
  std::cout << "a data after is " << a._data << std::endl;
  std::cout << "a2 data after is " << a2._data << std::endl;

  MyDouble<MyInt> my_double(5);
  const MyDouble<MyInt> const_double(5);
  MyInt my_int(my_double);
  MyInt my_int2(const_double);
  // MyInt my_int(std::string{});
}
