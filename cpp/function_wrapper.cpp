#include <iostream>
#include <functional>

class A
{
public:
  void function()
    {
      std::cout << "In function" << std::endl;
    }

  std::function<void()> functionWrapper;

  A()
    {
      functionWrapper = std::bind(&A::function, this);
    }
};

int main()
{
  A a;
  a.functionWrapper();
  std::function<void(A)> f = &A::function;
  f(a);
}
