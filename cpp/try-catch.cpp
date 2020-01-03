#include <stdexcept>
#include <iostream>

void foo()
{
  throw std::exception();
}

void bar()
{
  try
  {
    foo();
  }
  catch (std::logic_error &)
  {
    std::cout << "We caught a logic error\n";
  }
}

int main()
{
  try
  {
    bar();
  }
  catch (std::domain_error &)
  {
    std::cout << "We caught a domain error\n";
  }
  catch (std::runtime_error &)
  {
    std::cout << "We caught a runtime_error\n";
  }
  catch (std::exception &)
  {
    std::cout << "We caught the exception\n";
  }
}
