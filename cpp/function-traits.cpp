#include <map>
#include <iostream>

template <class F>
struct function_traits;

// function pointer
template <class R, class... Args>
struct function_traits<R (*)(Args...)> : public function_traits<R(Args...)>
{
};

template <class R, class... Args>
struct function_traits<R(Args...)>
{
  typedef R return_type;

  static constexpr std::size_t arity = sizeof...(Args);

  typedef std::tuple<Args...> args;

  template <std::size_t N>
  struct argument
  {
    static_assert(N < arity, "error: invalid parameter index.");
    typedef typename std::tuple_element<N, std::tuple<Args...>>::type type;
  };
};

// member function pointer
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...)> : public function_traits<R(C &, Args...)>
{
};

// const member function pointer
template <class C, class R, class... Args>
struct function_traits<R (C::*)(Args...) const> : public function_traits<R(C &, Args...)>
{
};

// member object pointer
template <class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C &)>
{
};

class A
{
public:
  void operator()() const { std::cout << "I'm the const version!\n"; }
  void operator()() { std::cout << "I'm the non-const version!\n"; }

  void memberFunction() {}

  // template <class... Args>
  // using fncPtr = void (A::*)(Args...) const;

  // std::map<typename function_traits<decltype
};

void
twoArgs(int, int)
{
}
void
oneArgs(int)
{
}
void
noArgs()
{
}

struct B
{
  void foo() const;
  void foo(int) const;

  using PFN_FOO = void (B::*)(int) const;
};

static_assert(std::is_same<B::PFN_FOO, decltype(static_cast<B::PFN_FOO>(&B::foo))>::value,
              "Ooops, need to update signature of PFN_FOO!");

int
main()
{
  std::map<typename function_traits<decltype(twoArgs)>::args, double> twoM;
  std::map<typename function_traits<decltype(oneArgs)>::args, double> oneM;
  std::map<typename function_traits<decltype(noArgs)>::args, double> zeroM;

  // std::map<typename function_traits<decltype(&A::operator())>::args, double> overloadM;
  // std::map<typename function_traits<&A::operator() const>::args, double> overloadM;
  std::map<typename function_traits<decltype(&A::memberFunction)>::args, double> memberM;

  void (A::*somebody)() const = &A::operator();
  void (A::*somebody_else)() = &A::operator();
  A a;
  (a.*somebody)();
  (a.*somebody_else)();
  std::map<typename function_traits<decltype(somebody)>::args, double> overloadM;
  std::map<typename function_traits<void (A::*)(int) const>::args, double> crazyM;
}
