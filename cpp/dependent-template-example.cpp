template <typename T> class A {
public:
  A() = default;

  T general_member;
};

template <> class A<int> {
public:
  A() = default;

  int specialized_member;
};

template <typename T> class B : public A<T> {
public:
  B() = default;
};

int main() {
  B<double>().general_member;
  B<int>().specialized_member;

  // Below errors because B<int> doesn't have general member
  // B<int>().general_member;
}
