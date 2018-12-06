template <bool B, class T = void>
struct enable_if_c
{
  typedef T type;
};
template <class T>
struct enable_if_c<false, T>
{
};
template <class Cond, class T = void>
struct enable_if : public enable_if_c<Cond::value, T>
{
};
template <bool B, class T>
struct lazy_enable_if_c
{
  typedef typename T::type type;
};
template <class T>
struct lazy_enable_if_c<false, T>
{
};
template <class Cond, class T>
struct lazy_enable_if : public lazy_enable_if_c<Cond::value, T>
{
};

template <class T, class U>
struct mult_traits
{
  typedef typename T::type type;
};

template <typename T, typename U>
struct is_multipliable
{
  static const bool value = false;
};

template <class T, class U>
typename lazy_enable_if_c<is_multipliable<T, U>::value, typename mult_traits<T, U>::type>::type
operator*(const T & t, const U & u)
{
}

struct A
{
};
struct B
{
};
int
main()
{
  A a;
  B b;
  auto result = 5 * 6;
  auto result2 = a * b;
}
