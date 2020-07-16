#include <memory>
#include <vector>

int main() {
  std::vector<std::unique_ptr<int>> a;
  a.emplace_back(std::make_unique<int>(5));
  auto b = std::move(a);
}
