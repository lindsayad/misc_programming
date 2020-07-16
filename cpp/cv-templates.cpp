#include <iostream>
#include <type_traits>

template <typename T> struct RawType { typedef T value_type; };

template <typename T> struct RawType<const T> {
  typedef const typename RawType<T>::value_type value_type;
};

template <typename T> struct IsRawSame {
  static constexpr bool value =
      std::is_same<T, typename RawType<T>::value_type>::value;
};

template <typename T, typename EnableT = T, typename Enable = void>
struct ValueTypeForRawTypeHelper;

template <typename T, typename EnableT>
struct ValueTypeForRawTypeHelper<
    T, EnableT, typename std::enable_if<IsRawSame<EnableT>::value>::type> {
  typedef const typename std::decay<T>::type &value_type;
};

template <typename T, typename EnableT>
struct ValueTypeForRawTypeHelper<
    T, EnableT, typename std::enable_if<!IsRawSame<EnableT>::value>::type> {
  typedef typename RawType<T>::value_type value_type;
};

struct Real {};
struct GeomReal {};

template <typename T> struct VectorValue {};

struct Point : public VectorValue<GeomReal> {};

template <>
struct ValueTypeForRawTypeHelper<
    Point, typename std::enable_if<IsRawSame<GeomReal>::value>::type> {
  typedef const Point &value_type;
};

// template <>
// struct ValueTypeForRawTypeHelper<
//     Point, typename std::enable_if<!IsRawSame<GeomReal>::value>::type> {
//   typedef VectorValue<Real> value_type;
// };

int main() {
  std::cout
      << std::is_same<typename ValueTypeForRawTypeHelper<Point>::value_type,
                      VectorValue<Real>>::value
      << std::endl;
}
