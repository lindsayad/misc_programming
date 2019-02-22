class A {
public:
  virtual ~A() {}
};

class B : public A {};

class C : public B {
public:
  C() { _x = new int(5); }

protected:
  // Even though the virtual keyword is not used, this destructor is still
  // virtual since a base declared a virtual destructor
  ~C() { delete _x; }

private:
  int *_x;
};

class D : public C {
public:
  D() { _y = new int(6); }

protected:
  // Even though the virtual keyword is not used, this destructor is still
  // virtual since a base declared a virtual destructor
  ~D() { delete _y; }

private:
  int *_y;
};

int main() {
  B *b = new C;
  delete b;

  B *b2 = new D;
  delete b2;

  // C *c = new D;
  // // Below causes compiler error because the (virtual) destructor ~C is
  // // protected and not public
  // delete c;
}
