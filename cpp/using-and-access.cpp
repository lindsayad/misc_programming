class A {
protected:
  int x;
};

class B : public A {
public:
  using A::x;
};

int main() { B b; }
