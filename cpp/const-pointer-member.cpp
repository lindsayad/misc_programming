struct A {
  double *pointer;

  A() : pointer(nullptr) {}
  A(double &d) : pointer(&d) {}
  A(double *d) : pointer(d) {}
};

int main() {

  double *d = new double(5);
  const A a(d);
  *a.pointer = 7;
}
