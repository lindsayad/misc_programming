#include <iostream>

template <typename T>
struct A
{
  A(const T & t) { std::cout << "Calling constructor\n"; }

  A & operator=(const T & t)
  {
    std::cout << "Calling assignmnet operator\n";
    return *this;
  }
};

int
main()
{
  A<int> a(0);
  a = 0;
}
