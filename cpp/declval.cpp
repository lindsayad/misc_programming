#include <utility>
#include <iostream>

struct Default
{
  int foo() const { return 1; }
  int bar(int) { return 1; }
};

struct NonDefault
{
  NonDefault(const NonDefault &) {}
  int foo() const { return 1; }
  int bar(int) { return 1; }
};

struct A
{
  void do_nothing(int, int) const {}
};

struct B
{
};

template <typename T, typename... Args>
auto
do_nothing(int, const T & t, Args &&... args)
    -> decltype(t.do_nothing(std::forward<Args>(args)...), void())
{
  std::cout << "Called the sfinae!" << std::endl;
}

template <typename T, typename... Args>
void
do_nothing(double, const T & t, Args &&... args)
{
  std::cout << "Called the non-sfinae!" << std::endl;
}

int
main()
{
  decltype(Default().foo()) n1 = 1; // type of n1 is int
  //  decltype(NonDefault().foo()) n2 = n1;               // error: no default constructor
  decltype(std::declval<NonDefault>().foo()) n2 = n1; // type of n2 is int
  std::cout << "n1 = " << n1 << '\n' << "n2 = " << n2 << '\n';
  decltype(std::declval<Default>().bar(int())) n3 = 5;
  decltype(std::declval<NonDefault>().bar(int())) n4 = 7;
  // decltype(std::declval<NonDefault>().bar()) n5 = 7; // error: too few arguments to function call
  A a;
  B b;
  do_nothing(int(), a, int(), int());
  do_nothing(int(), b, int(), int());
}
