class A
{
protected:
  int value = 0;
};

class AA
{
protected:
  int value = 0;
};

class B : public A, public AA
{
public:
  B() : value2(A::value) {}

protected:
  int value2;
};

int
main()
{
  B b;
  return 0;
}
