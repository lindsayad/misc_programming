#include <vector>
#include <iostream>

class A
{
public:
  A() { std::cout << "empty constructor" << std::endl;}
  A(const A & other) :
      _vec(other._vec)
    {
      std::cout << "Copy constructor" << std::endl;
    }
  A(A&& other) :
      _vec(std::move(other._vec)){
    std::cout << "move constructor" << std::endl;
  }

  ~A() { std::cout << "destructor called" << std::endl; }

  A& operator=(const A & other)
    {
      _vec = other._vec;
      std::cout << "copy assignment" << std::endl;
      return *this;
    }
  A& operator=(A&& other)
    {
      _vec = std::move(other._vec);
    std::cout << "move assignment" << std::endl;
    return *this;
  }

private:
  std::vector<int> _vec;
};

A
foo()
{
  // A a;
  // return a;
  return {};
}

int main()
{
  // // Previous code
  // A a;
  // for (unsigned int i = 0; i < 2; ++i)
  //   a = foo();

  // Current code
  for (unsigned int i = 0; i < 2; ++i)
    A a = foo();
}
