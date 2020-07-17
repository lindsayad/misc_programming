#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  static string reverseStr(string s, int k) {
    auto n = s.size();

    if (n < k) {
      for (decltype(n) i = 0; i < n / 2; ++i)
        swap(s[i], s[n - i - 1]);
      return s;
    }

    decltype(n) counter = 0;

    for (; counter <= n; counter += 2 * k) {
      auto remaining_letters = n - counter;
      auto letters_to_reverse = remaining_letters < k ? remaining_letters : k;
      for (decltype(n) i = 0; i < letters_to_reverse / 2; ++i)
        swap(s[counter + i], s[counter + letters_to_reverse - i - 1]);
    }

    // counter -= 2*k;
    // auto beginning_index = counter;

    // for (decltype(n) i = 0; i < k / 2 && counter < n; ++i, ++counter)
    //     swap(s[beginning_index +i], s[beginning_index + k - i - 1]);

    return s;
  }
};

int main() {
  std::vector<std::pair<std::string, int>> inputs = {
      std::make_pair("abcdefg", 2), std::make_pair("a", 3),
      std::make_pair("abcdefg", 3)};
  for (const auto &input : inputs)
    std::cout << Solution::reverseStr(input.first, input.second) << std::endl;
}
