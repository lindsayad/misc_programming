
template <typename T>
class A
{
public:
  A() {}
};

class B : public A<T>
{
public:
  template <typename T>
  B(T * /*t*/) : A() {}
};

template <typename T>
class C : public B
{
public:
  C() : B(this) {}
};

int main()
{
  C<int> c;
}
