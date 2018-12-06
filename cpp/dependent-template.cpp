template <typename T, typename U>
class A
{
};

template <typename T, typename U>
class B : public A<T, U>
{
};

template <typename U>
class B<int, U> : public A<int, U>
{
};

int
main()
{
  B<int, double> b;
}
