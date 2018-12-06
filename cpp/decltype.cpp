#include <vector>
#include <iostream>
#include <type_traits>
#include <utility>

class A
{
public:
  A(int) { std::cout << "Calling A constructor\n"; }
  A() = default;

  void test()
  {
    std::cout << std::is_same<decltype(this), A *>::value << std::endl;
    std::cout << std::is_same<decltype(*this), A &>::value << std::endl;
    std::cout << std::is_same<decltype(*this) &, A &&>::value << std::endl;
    std::cout << std::is_same<typename std::remove_reference<decltype(*this)>::type &&, A &&>::value
              << std::endl;
  }

  virtual auto create_new_thing() -> typename std::remove_reference<decltype(*this)>::type &&
  {
    return {int()};
  }
};

class B : public A
{
public:
  B(int) { std::cout << "Calling B ructor\n"; }
  B() = default;

  virtual auto create_new_thing() ->
      typename std::remove_reference<decltype(*this)>::type && override
  {
    return {int()};
  }
};

int
main()
{
  A a;
  a.test();
  B b;
  // auto new1 = std::move(a.create_new_thing());
  // auto new2 = std::move(b.create_new_thing());
}
