#include <utility>

class A
{
public:
  template <typename T>
  T method(const T & t)
  {
    return t;
  }

  void method(const int & i) {}
  void method(const int & i) const {}
};

template <typename R,
          typename TMethod,
          typename TObject,
          typename... PtrArgs,
          typename... ParamArgs>
void
return_helper(R (TMethod::*fn)(PtrArgs...), TObject & object, ParamArgs &&... args)
{
  (object.*fn)(std::forward<ParamArgs>(args)...);
}

template <typename TMethod, typename TObject, typename... PtrArgs, typename... ParamArgs>
void
helper(void (TMethod::*fn)(PtrArgs...), TObject & object, ParamArgs &&... args)
{
  (object.*fn)(std::forward<ParamArgs>(args)...);
}

template <typename TMethod, typename TObject, typename... PtrArgs, typename... ParamArgs>
void
const_helper(void (TMethod::*fn)(PtrArgs...) const, TObject & object, ParamArgs &&... args)
{
  (object.*fn)(std::forward<ParamArgs>(args)...);
}

int
main()
{
  A a;
  helper<A>(&A::method, a, 5);
  const_helper<A>(&A::method, a, 5);
  return_helper<int, A>(&A::method, a, 5);
}
