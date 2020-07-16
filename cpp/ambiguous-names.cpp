#include <iostream>

namespace MetaPhysicL {
struct A {
  A() {}
};

template <typename T> void foo(T) {}

template <typename> struct RawType {};
} // namespace MetaPhysicL

namespace libMesh {

using MetaPhysicL::RawType;

template <> struct RawType<double> {};
} // namespace libMesh

int main() {}
