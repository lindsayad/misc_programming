#include <utility>

struct A
{
  void method() {}

  void method2(int) {}
};

struct B : A
{
  // void method2(int) {}
};

template <typename T>
class C
{
public:
  T t;
};

// Case 1
// template <typename T, typename R>
// void
// test(R (T::*fn)(), C<T> & c)
// {
//   (c.t.*fn)();
// }

// Case 2
// template <typename R, typename T>
// void
// test(R (T::*fn)(), C<T> & c)
// {
//   (c.t.*fn)();
// }

// Case 3
template <typename T, typename TBase, typename R, typename... PtrArgs, typename... ParamArgs>
void
test(R (TBase::*fn)(PtrArgs...), C<T> & c, ParamArgs &&... args)
{
  (c.t.*fn)(std::forward<ParamArgs>(args)...);
}

int
main()
{
  C<B> c;

  // Case 1

  // Below compiles
  // test<B, void>(&B::method, c);

  // Below errors because: candidate template ignored: could not match 'B' against 'A'
  // test<B>(&B::method, c);

  // Case 2

  // Below compiles
  // test<void, B>(&B::method, c);

  // Below Errors because: candidate template ignored: deduced conflicting
  // types for parameter 'T' ('A' vs. 'B')
  // test<void>(&B::method, c);

  // Case 3

  // Below compiles
  test(&B::method, c);
  // Below errors for second template candidate: candidate function not viable: no known conversion
  // from 'void (A::*)(int)' to 'void (B::*)()' for 1st argument
  // Below error for first template
  // candidate: candidate template ignored: could not match 'B' against 'A'
  test(&B::method2, c, 5);
}
