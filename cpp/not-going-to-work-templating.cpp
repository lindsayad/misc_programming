#include <utility>
#include <type_traits>

template <typename T>
struct A
{
};

// The below partial specialization is a scanario where the new template parameter T cannot be
// deduce template <typename T> struct A<
//     typename std::enable_if<std::is_same<T, int>::value || std::is_same<T, double>::value,
//     T>::type>
// {
//   void method() {}
// };

template <typename T>
void
test(const T & t)
{
  t.method();
}

int
main()
{
  A<int> a;
  test(a);
  // a.method();
}
