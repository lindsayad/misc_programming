#include <unordered_map>

enum class Test
{
  Yes,
  No
};

int
main()
{
  std::unordered_map<Test, double> test;
  test[Test::Yes] = 1;
}
