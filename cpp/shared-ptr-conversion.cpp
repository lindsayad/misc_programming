#include <memory>

class A
{
public:
  virtual ~A() = default;
};

class B : public A
{
};

void foo(std::shared_ptr<const A>) {}

int
main()
{
  auto b = std::make_shared<B>();
  foo(b);
}
