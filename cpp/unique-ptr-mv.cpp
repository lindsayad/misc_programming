#include <memory>

class A {};

class B : public A {};

int main() {
  auto b = std::make_unique<B>();

  std::unique_ptr<A> a;

  a = std::move(b);
}
