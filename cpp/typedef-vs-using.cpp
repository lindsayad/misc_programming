template <typename T> class B {
public:
  typedef T BType;
};

template <typename T> class A {
public:
  typedef B<T> AType;
  typedef typename B<T>::BType
      AType2; // Need typename because BType is dependent on `T`

  template <typename U>
  using SomeType =
      typename B<U>::BType; // Need typename because BType is dependent on `U`
};

typedef A<int>::AType MainType;
using MainType2 = A<int>::AType;

template <typename T>
using TemplateType = typename A<T>::AType; // Again, need typename because AType
                                           // is dependent on `T`

using AnotherType = B<int>;

int main() {}
