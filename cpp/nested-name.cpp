#include <vector>

typedef double Real;
typedef double GeomReal;
template <typename T> using VectorValue = std::vector<T>;
typedef VectorValue<Real> RealVectorValue;

template <typename> struct MakeOutput;

template <> struct MakeOutput<Real> { typedef GeomReal type; };
template <> struct MakeOutput<RealVectorValue> {
  typedef VectorValue<GeomReal> type;
};

template <typename OutputType> class FE {
public:
  typedef typename MakeOutput<OutputType>::type OutputShape;
};

int main() { FE<double> fe; }
