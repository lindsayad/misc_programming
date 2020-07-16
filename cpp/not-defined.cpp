class A
{
public:
  virtual ~A();

  virtual void foo();
};

A::~A() {}

int main()
{
  A a;
}
