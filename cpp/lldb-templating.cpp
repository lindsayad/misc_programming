#include <complex>

template <typename T>
class A
{
public:
  A(T x)
    {
      y = x;
    }

  T y;
};

class B
{
public:
  B(int x)
    {
      y = x;
    }
  int y;
};

typedef A<int> IntA;
typedef double my_double;


int main()
{
  double i = 5.;
  A<int> a(5);
  B b(5);
}
