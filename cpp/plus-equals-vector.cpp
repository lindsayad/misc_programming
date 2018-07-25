#include <vector>

using namespace std;

int main() {
  vector<double> v{1., 2., 3.};
  vector<double> w{4., 5., 6.};
  w += v;
  for (auto &value : w)
    std::cout << value << std::endl;
}
