// template <typename T>
// T f(T && temp);

template <typename T>
class A
{
public:
  auto my_method() -> decltype(f(T())) { return f(T()); }
};

template <typename T>
T
f(T && temp)
{
  return temp;
}

int
main()
{
  // A<double> a;
  // double temp = a.my_method();
  int i = 5;
  i += 1;
}
