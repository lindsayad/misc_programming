#include <iostream>
#include <set>
#include <type_traits>
#include <utility>
#include <vector>

namespace libMesh {
namespace Parallel {
template <typename T, typename Enable = void> class Packing {};

// Idiom taken from
// https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Member_Detector
template <typename T> class Has_buffer_type {
  using Yes = char[2];
  using No = char[1];

  struct Fallback {
    struct buffer_type {};
  };
  struct Derived : T, Fallback {};

  template <typename U> static Yes &test(U *);

  // this template must be more specialized in general than the Yes version
  // because it involves a type-dependent expression...?
  template <typename U> static No &test(typename U::buffer_type *);

public:
  static constexpr bool value = sizeof(test<Derived>(nullptr)) == sizeof(Yes);
};

template <typename T1, bool T1_has_buffer_type, typename T2,
          bool T2_has_buffer_type>
struct PairBufferTypeHelper {};

template <typename T1, typename T2>
struct PairBufferTypeHelper<T1, true, T2, true> {
  static_assert(
      std::is_same<typename T1::buffer_type, typename T2::buffer_type>::value,
      "For ease of use we cannot pack two types that use two different buffer "
      "types");

  typedef typename T1::buffer_type buffer_type;
};

template <typename T1, typename T2>
struct PairBufferTypeHelper<T1, true, T2, false> {
  typedef typename T1::buffer_type buffer_type;
};

template <typename T1, typename T2>
struct PairBufferTypeHelper<T1, false, T2, true> {
  typedef typename T2::buffer_type buffer_type;
};

template <typename T> class Packing<std::set<T>> {
public:
  static const unsigned int size_bytes = 4;

  typedef T buffer_type;

  static unsigned int get_set_len(typename std::vector<T>::const_iterator in) {
    unsigned int set_len =
        reinterpret_cast<const unsigned char &>(in[size_bytes - 1]);
    for (signed int i = size_bytes - 2; i >= 0; --i) {
      set_len *= 256;
      set_len += reinterpret_cast<const unsigned char &>(in[i]);
    }
    return set_len;
  }

  static unsigned int packed_size(typename std::vector<T>::const_iterator in) {
    return get_set_len(in) + size_bytes;
  }

  static unsigned int packable_size(const std::set<T> &s, const void *) {
    return s.size() + size_bytes;
  }

  template <typename Iter>
  static void pack(const std::set<T> &b, Iter data_out, const void *) {
    unsigned int set_len = b.size();
    for (unsigned int i = 0; i != size_bytes; ++i) {
      *data_out++ = (set_len % 256);
      set_len /= 256;
    }
    std::copy(b.begin(), b.end(), data_out);
  }

  static std::set<T> unpack(typename std::vector<T>::const_iterator in,
                            void *) {
    unsigned int set_len = get_set_len(in);

    return std::set<T>(in + size_bytes, in + size_bytes + set_len);
  }
};

} // namespace Parallel

} // namespace libMesh

using namespace libMesh::Parallel;

int main() {

  std::pair<std::set<unsigned int>, unsigned int> pr;

  typedef decltype(pr.first) type1;
  typedef decltype(pr.second) type2;

  std::cout << Has_buffer_type<Packing<type1>>::value << std::endl;
  // typedef PairBufferTypeHelper<
  //     type1, Has_buffer_type<Packing<type1>>::value, type2,
  //     Has_buffer_type<Packing<type2>>::value>::buffer_type main_buffer_type;
};
