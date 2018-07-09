class A
{
public:
  virtual void linesearch(void * ls_object) {}
};

class B : public A
{
public:
  virtual void linesearch(void * ls_object) override {}
};

int main()
{
  A a;
  B b;
}
