#include <iostream>

enum ComputeStage
{
  RESIDUAL,
  JACOBIAN
};

template <ComputeStage compute_stage>
class A
{
public:
  virtual void foo() { std::cout << "Calling the base class method\n"; }
};

template <ComputeStage compute_stage>
class B : public A<compute_stage>
{
public:
  void foo() override
  {
    std::cout << "Calling the derived class method\n";
    A<compute_stage>::foo();
  }
};

int
main()
{
  B<RESIDUAL> b;
  b.foo();
}
