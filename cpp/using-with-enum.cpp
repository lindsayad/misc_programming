template <typename T> class Base {
public:
  enum Color { RED, BLUE, GREEN };
};

template <typename T> class Derived : public Base<T> {
public:
  typedef Base<T> Base2;

  using Base2::Color;
};

int main() {}
