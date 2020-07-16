class A {};

template <typename T> class B : public A {};

template <> class B<int> {};

template <typename> class StandardType;

template <> class StandardType<int> {};

int main() {
  B<double> bd;
  B<int> bi;
}
