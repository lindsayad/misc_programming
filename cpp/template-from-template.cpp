#include <type_traits>
#include <map>
#include <vector>
#include <set>
#include <iostream>

template <typename T>
class A
{
};

template <>
class A<double>
{
};

template <>
class A<int> : public A<double>
{
};

template <typename T>
class B
{
};

template <typename T, template <typename> class W>
struct is_same_template : std::false_type
{
};

template <template <typename> class W, typename T>
struct is_same_template<W<T>, W> : std::true_type
{
};

int
main()
{
  std::cout << is_same_template<A<int>, A>::value << std::endl;
  std::cout << is_same_template<A<int>, B>::value << std::endl;
}
