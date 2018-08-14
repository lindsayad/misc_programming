#include <functional>
#include <iostream>

class A {
public:
  void function() { std::cout << "In function" << std::endl; }

  std::function<void()> functionWrapper;

  A() { functionWrapper = std::bind(&A::function, this); }

  int function2(int x) {
    _x = 7;
    std::cout << "In function2" << std::endl;
    return x;
  }

  const int &x() { return _x; }

private:
  int _x;
};

struct D {
  void twoArgs(const int &, const int &) { std::cout << "Called two args!\n"; }

  void oneArg(const int &) { std::cout << "called one args\n"; }

  void noArgs() { std::cout << "called no args\n"; }

  int returnAnInt() {
    std::cout << "returning an int\n";
    return 5;
  }
};

template <typename R, typename T, class... Args, class... Args2>
void do_all_the_things(std::function<R(T &, Args...)> f, T &object,
                       Args2... a) {
  f(object, a...);
}

template <typename T, class... Args, class... Args2>
void do_all_the_things2(void (T::*fn)(Args...), T &object, Args2 &&... a) {
  (object.*fn)(std::forward<Args2>(a)...);
}

template <typename R, typename T, class... Args, class... Args2>
R do_all_the_things2(R (T::*fn)(Args...), T &object, Args2 &&... a) {
  return (object.*fn)(std::forward<Args2>(a)...);
}

struct B {
  D a;

  void twoArgs(const int &arg1, const int &arg2) {
    do_all_the_things(
        std::function<void(D &, const int &, const int &)>(&D::twoArgs), a,
        arg1, arg2);
  }

  void oneArg(const int &arg1) {
    do_all_the_things(std::function<void(D &, const int &)>(&D::oneArg), a,
                      arg1);
  }

  void noArgs() { do_all_the_things(std::function<void(D &)>(&D::noArgs), a); }
};

#define ForwardToMemberDecl(methodName)                                        \
  template <class... Args>                                                     \
  auto methodName(Args &&... args)->decltype(a.methodName(args...))

#define ForwardToMemberDef(methodName)                                         \
  template <class... Args>                                                     \
  auto E::methodName(Args &&... args)->decltype(a.methodName(args...)) {       \
    do_all_the_things2(&D::methodName, a, std::forward<Args>(args)...);        \
  }                                                                            \
  void ANONYMOUS_FUNCTION()

struct E {
  D a;

  ForwardToMemberDecl(twoArgs);
  ForwardToMemberDecl(oneArg);
  ForwardToMemberDecl(noArgs);
  ForwardToMemberDecl(returnAnInt);
};

ForwardToMemberDef(twoArgs);
ForwardToMemberDef(oneArg);
ForwardToMemberDef(noArgs);
ForwardToMemberDef(returnAnInt);

int main() {
  A a;
  a.functionWrapper();
  std::function<void(A)> f = &A::function;
  f(a);
  std::function<int(A &, int)> f2 = &A::function2;
  std::cout << "int is " << a.x() << std::endl;
  f2(a, 5);
  std::cout << "int is " << a.x() << std::endl;

  std::function<int(A, int)> f3 = &A::function2;
  std::cout << "int is " << a.x() << std::endl;
  f3(a, 5);
  std::cout << "int is " << a.x() << std::endl;

  do_all_the_things(f2, a, 5);

  B b;
  b.twoArgs(int(), int());
  b.oneArg(int());
  b.noArgs();

  E e;
  e.twoArgs(int(), int());
  e.oneArg(int());
  e.noArgs();
  e.returnAnInt();
}
