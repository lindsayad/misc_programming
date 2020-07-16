#include <array>

template <typename N> class A { std::array<double, N::size> a; };

template <std::size_t N> struct NWrapper { static const size_t size = N; };

int main() { A<NWrapper<5>> a; }
