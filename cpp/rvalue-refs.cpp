#include <iostream>

static unsigned counter = 0;

class A
{
public:
  A() { ++counter; }
};

A
f()
{
  return A{};
}

void
push_back(A &&)
{
}

int
main()
{
  push_back(f());
  std::cout << counter << std::endl;
  auto && i = f();
  push_back(std::move(i));
}
