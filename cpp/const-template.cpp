template <typename T>
void
foo(T &)
{
}

int
main()
{
  const int i = 0;
  double j = 0;
  foo(i);
  foo(j);
}
