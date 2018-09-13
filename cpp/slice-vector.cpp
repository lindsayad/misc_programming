#include <vector>

int main()
{
  std::vector<double> a = {1, 2, 3, 4};
  std::vector<double> b(a.begin(), a.end());
  std::vector<double> c(&a[0], &a[a.size() - 1]);
  int z = 5;
}
