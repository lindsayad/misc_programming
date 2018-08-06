int main() {
  double a = 5;
  auto &b = a;
  const auto &c = a;
  b = b * c;
}
