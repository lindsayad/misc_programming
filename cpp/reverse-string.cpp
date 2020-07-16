#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    static string reverseStr(string s, int k) {
        auto n = s.size();

        if (n < k)
        {
            for (decltype(n) i = 0; i < n / 2; ++i)
                swap(s[i], s[n - i - 1]);
            return s;
        }

        decltype(n) counter = 0;

        for (; counter <= n; counter += 2 * k)
            for (decltype(n) i = 0; i < k / 2; ++i)
                swap(s[counter + i], s[counter + k - i - 1]);

        // counter -= 2*k;
        // auto beginning_index = counter;

        // for (decltype(n) i = 0; i < k / 2 && counter < n; ++i, ++counter)
        //     swap(s[beginning_index +i], s[beginning_index + k - i - 1]);

        return s;
    }
};

int main()
{
  auto result = Solution::reverseStr("abcdefg", 3);
  std::cout << result << std::endl;
}
