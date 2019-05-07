int
foo(const float * const & a)
{
  return 0;
}

int
main()
{
  float * a;
  foo(a);

  return 0;
}
