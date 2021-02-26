struct GeomReal
{
  static const bool is_fixed_type = true;
};

struct DataType {};
struct NotADataType {};

template <bool>
struct MaybeADataType {
  typedef DataType type;
};

template <>
struct MaybeADataType<false>
{
  typedef NotADataType type;
};

class A : public MaybeADataType<GeomReal::is_fixed_type>::type
{
public:
  A() = default;
};

int main()
{
  A a;
}
