template <typename T> class MeshBase {
public:
  typedef const T const_elem_iterator;
};

template <typename IteratorType> void foo(const IteratorType &) {}

template void foo(const typename MeshBase<double>::const_elem_iterator &);

int main() {}
