#include <iostream>

template <typename T, typename T2, typename enable = void>
struct CompareTypes;
template <typename T2>
struct CompareTypes<double, T2, typename std::enable_if<!std::is_same<T2, double>::value>::type>
{
  typedef double type;
};
template <typename T>
struct CompareTypes<T, double, typename std::enable_if<!std::is_same<T, double>::value>::type>
{
  typedef double type;
};
template <typename T>
struct CompareTypes<T, T>
{
  typedef T type;
};

template <typename T>
class A
{
public:
  template <typename T2>
  A<typename CompareTypes<T, T2>::type> operator*(const A<T2> &);
};

template <typename T>
template <typename T2>
A<typename CompareTypes<T, T2>::type> A<T>::operator*(const A<T2> &)
{
  return A<typename CompareTypes<T, T2>::type>();
}

template <typename T>
class B : public A<T>
{
public:
  // // Adding this method results in compilation error!
  // template <typename T2>
  // B<typename CompareTypes<T, T2>::type> operator*(const B<T2> &);
};

// // Adding this method results in compilation error!
// template <typename T>
// template <typename T2>
// B<typename CompareTypes<T, T2>::type> B<T>::operator*(const B<T2> &)
// {
//   return B<typename CompareTypes<T, T2>::type>();
// }

int
main()
{
  B<int> b1;
  B<double> b2;
  b1 * b1;
  b1 * b2;
  b2 * b1;
  b2 * b2;
  A<int> a1;
  A<double> a2;
  a1 * a1;
  a1 * a2;
  a1 * b1;
  a1 * b2;
  a2 * a1;
  a2 * a2;
  a2 * b1;
  a2 * b2;
  b1 * a1;
  b1 * a2;
  b1 * b1;
  b1 * b2;
  b2 * a1;
  b2 * a2;
  b2 * b1;
  b2 * b2;
}
