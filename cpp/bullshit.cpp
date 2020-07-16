#include <iostream>

// Idiom taken from
// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
#define GENERATE_HAS_MEMBER_TYPE(Type)                                         \
  template <class T> class HasMemberType_##Type {                              \
  private:                                                                     \
    using Yes = char[2];                                                       \
    using No = char[1];                                                        \
                                                                               \
    struct Fallback {                                                          \
      struct Type {};                                                          \
    };                                                                         \
    struct Derived : T, Fallback {};                                           \
                                                                               \
    template <class U> static No &test(typename U::Type *);                    \
    template <typename U> static Yes &test(U *);                               \
                                                                               \
  public:                                                                      \
    static constexpr bool value =                                              \
        sizeof(test<Derived>(nullptr)) == sizeof(Yes);                         \
  };                                                                           \
  template <> class HasMemberType_##Type<double> {                             \
  public:                                                                      \
    static constexpr bool value = false;                                       \
  }

GENERATE_HAS_MEMBER_TYPE(OutputShape);

struct Bullshit {
  typedef double OutputShape;
};

typedef double Real;

int main() {
  std::cout << HasMemberType_OutputShape<Bullshit>::value << std::endl;
  std::cout << HasMemberType_OutputShape<double>::value << std::endl;
  std::cout << HasMemberType_OutputShape<Real>::value << std::endl;
}
