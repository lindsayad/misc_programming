template <typename = void> class A;

template <typename> class A;

template <typename = void> class A;

template <typename> class A {};

int main() { A<int> a; }
