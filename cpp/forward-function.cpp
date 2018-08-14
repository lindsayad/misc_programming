#include <iostream>

struct D {
  void twoArgs(const int &, const int &) { std::cout << "Called two args!\n"; }

  void oneArg(const int &) { std::cout << "called one args\n"; }

  void noArgs() { std::cout << "called no args\n"; }

  int returnAnInt() {
    std::cout << "returning an int\n";
    return 5;
  }
};

template <typename T, class... Args, class... Args2>
void do_all_the_things(void (T::*fn)(Args...), T &object, Args2 &&... a) {
  (object.*fn)(std::forward<Args2>(a)...);
}

template <typename R, typename T, class... Args, class... Args2>
R do_all_the_things(R (T::*fn)(Args...), T &object, Args2 &&... a) {
  return (object.*fn)(std::forward<Args2>(a)...);
}

#define ForwardToMemberDecl(methodName)                                        \
  template <class... Args>                                                     \
  auto methodName(Args &&... args)->decltype(a.methodName(args...))

#define ForwardToMemberDef(methodName)                                         \
  template <class... Args>                                                     \
  auto E::methodName(Args &&... args)->decltype(a.methodName(args...)) {       \
    do_all_the_things(&D::methodName, a, std::forward<Args>(args)...);         \
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
  E e;
  e.twoArgs(int(), int());
  e.oneArg(int());
  e.noArgs();
  e.returnAnInt();
}
