#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

template <typename T> struct RealTraits { static const bool value = false; };

#define RealTraits_true(type)                                                  \
  template <> struct RealTraits<type> { static const bool value = true; }

RealTraits_true(float);
RealTraits_true(double);
RealTraits_true(long double);

template <typename T> class VectorValue {};

template <typename T> struct MathWrapperTraits {
  static constexpr bool value = false;
};

template <typename T> struct MathWrapperTraits<VectorValue<T>> {
  static constexpr bool value = true;
};

template <typename T, typename enable = void> struct MakeBaseNumber {};

template <typename T>
struct MakeBaseNumber<T, typename std::enable_if<RealTraits<T>::value>::type> {
  typedef T type;
};

template <template <typename> class Wrapper, typename T>
struct MakeBaseNumber<
    Wrapper<T>,
    typename std::enable_if<MathWrapperTraits<Wrapper<T>>::value>::type> {
  typedef T type;
};

template <typename T, typename Enable = void> struct StandardType {
  static void foo() { std::cout << "Generic template\n"; }

  static constexpr bool is_fixed_type = true;
};

template <typename T>
struct StandardType<VectorValue<T>,
                    typename std::enable_if<RealTraits<T>::value>::type> {
  static void foo() { std::cout << "Vector value, real traits\n"; }

  static constexpr bool is_fixed_type = StandardType<T>::is_fixed_type;
};

template <typename T>
struct StandardType<VectorValue<T>,
                    typename std::enable_if<!RealTraits<T>::value>::type> {
  static void foo() { std::cout << "Vector value, non-real traits\n"; }

  static constexpr bool is_fixed_type = StandardType<T>::is_fixed_type;
};

template <typename Head, typename... Tail> struct CheckAllFixedTypes {
  static constexpr bool is_fixed_type =
      StandardType<Head>::is_fixed_type &&
      CheckAllFixedTypes<Tail...>::is_fixed_type;
};

template <typename Head> struct CheckAllFixedTypes<Head> {
  static constexpr bool is_fixed_type = StandardType<Head>::is_fixed_type;
};

template <typename... Args> struct StandardType<std::tuple<Args...>> {
  static void foo() { std::cout << "tuple overload\n"; }

  static constexpr bool is_fixed_type =
      CheckAllFixedTypes<Args...>::is_fixed_type;
};

struct Communicator {
  template <typename T, typename std::enable_if<StandardType<T>::is_fixed_type,
                                                int>::type = 0>
  void allgather(const T &) {
    std::cout << "Called the fixed size method\n";
  }

  template <typename T, typename std::enable_if<!StandardType<T>::is_fixed_type,
                                                int>::type = 0>
  void allgather(const T &t) {
    allgather_packed_range(t);
  }

  template <typename T> void allgather_packed_range(const T &) {
    std::cout << "Called the packed range method\n";
  }
};

template <typename T> struct StandardType<std::vector<T>> {
  static constexpr bool is_fixed_type = false;
};

int main() {
  // typename MakeBaseNumber<double>::type blah = 2;

  // VectorValue<double> vector;
  // std::cout << MathWrapperTraits<VectorValue<double>>::value << std::endl;
  // // typename MakeBaseNumber<decltype(vector)>::type blaaaaah = 3;
  // typename MakeBaseNumber<VectorValue<double>>::type blah2 = 3;

  // std::cout << std::is_same<decltype(blah2), decltype(blah)>::value
  //           << std::endl;
  // std::cout << std::is_same<decltype(blah2), double>::value << std::endl;

  StandardType<int>::foo();
  StandardType<VectorValue<double>>::foo();
  StandardType<VectorValue<int>>::foo();
  std::cout << StandardType<std::tuple<unsigned int, unsigned int,
                                       unsigned int>>::is_fixed_type
            << std::endl;

  Communicator comm;
  int a = 5;
  std::vector<double> vec;

  comm.allgather(a);
  comm.allgather(vec);
}
