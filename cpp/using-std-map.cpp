#include <map>

class A
{
public:
  template <typename KeyType, typename ValueType>
  using Map = std::map<KeyType, ValueType>;

  Map<unsigned, double> a_map;
};

int
main()
{
  A a;
  a.a_map[5] = 6.;
}
