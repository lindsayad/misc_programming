#include <iostream>
#include <utility>

class DataType {
public:
  void free() { std::cout << "I'm the base\n"; }
};

template <typename T, typename Enable = void> class StandardType {
public:
  static const bool is_fixed_type = false;

  /*
   * The unspecialized class is useless, so we make its constructor
   * private to catch mistakes at compile-time rather than link-time.
   * Specializations should have a public constructor of the same
   * form.
   */
private:
  StandardType(const T *example = nullptr);
};

template <> class StandardType<double> {
public:
  static const bool is_fixed_type = true;
};
// template <> class StandardType<int> {
// public:
//   static const bool is_fixed_type = true;
// };

typedef int GeomReal;
template <typename T> class Point {
public:
  T x;
};

class PointNoTemplate {};

template <typename T>
class StandardType<
    Point<T>, typename std::enable_if<StandardType<T>::is_fixed_type>::type> {
public:
  static const bool is_fixed_type = true;
};

// template <typename T>
// class StandardType<
//     Point<T>, typename std::enable_if<!StandardType<T>::is_fixed_type>::type>
//     {
// public:
//   static const bool is_fixed_type = false;
// };

template <> class StandardType<PointNoTemplate> : public DataType {
public:
  template <
      typename T = GeomReal,
      typename std::enable_if<StandardType<T>::is_fixed_type, int>::type = 0>
  explicit StandardType(const PointNoTemplate *example = nullptr) {}

  StandardType() = default;

  template <
      typename T = GeomReal,
      typename std::enable_if<StandardType<T>::is_fixed_type, int>::type = 0>
  void free() {
    std::cout << "I'm the derived\n";
    DataType::free();
  }

  template <
      typename T = GeomReal,
      typename std::enable_if<!StandardType<T>::is_fixed_type, int>::type = 0>
  void free() {
    std::cout << "I'm the derived\n";
    // DataType::free();
  }

  ~StandardType() { this->free(); }

  static const bool is_fixed_type = StandardType<GeomReal>::is_fixed_type;
};

// template <typename T = GeomReal>
// class StandardType<
//     PointNoTemplate,
//     typename std::enable_if<!StandardType<T>::is_fixed_type>::type> {
// public:
//   static const bool is_fixed_type = false;
// };

int main() {
  std::cout << StandardType<Point<double>>::is_fixed_type << std::endl;
  std::cout << StandardType<Point<int>>::is_fixed_type << std::endl;
  std::cout << StandardType<PointNoTemplate>::is_fixed_type << std::endl;

  PointNoTemplate point;
  // StandardType<PointNoTemplate> st(&point);
  StandardType<PointNoTemplate> st2;
}
