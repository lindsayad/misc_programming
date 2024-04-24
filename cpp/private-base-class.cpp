class A
{
};

class B : public A
{
};

int
main()
{
  B b;
  // Below is compiler error: ‘A’ is an inaccessible base of ‘B’
  // A * a_ptr = &b;
  // Below is the same error
  auto a_ptr = dynamic_cast<A *>(&b);
}
