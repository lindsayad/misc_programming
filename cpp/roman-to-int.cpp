#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        if (s.empty())
            return 0;

        unordered_map<const char *, int> roman_to_int = {std::make_pair("I", 1),
                                      std::make_pair("V", 5),
                                      std::make_pair("X", 10),
                                      std::make_pair("L", 50),
                                      std::make_pair("C", 100),
                                      std::make_pair("D", 500),
                                      std::make_pair("M", 1000)};

        if (s.size() == 1)
            return roman_to_int[&s[0]];

        int sum = 0;

        for (auto it = s.begin(); it != s.end();)
        {
            vector<int> nums(1, roman_to_int[&(*it)]);
            bool standard_order = true;

            // Ok, we just read a number
            ++it;

            while (it != s.end())
            {
                auto next_num = roman_to_int[&(*it)];
                if (next_num <= nums.back())
                    break;
                else
                {
                    // This number is greater than the previous so we are reversing
                    // the order
                    standard_order = false;

                    nums.push_back(next_num);

                    // Read a number
                    ++it;
                }
            }

            if (standard_order)
            {
                // We only read one number hopefully
                assert(nums.size() == 1);
                sum += nums.front();
            }
            else
            {
                assert(nums.size() > 1);
                int sum_this_loop = nums.back();
                for (auto nums_it = nums.rbegin() + 1; nums_it != nums.rend(); ++nums_it)
                    sum_this_loop -= *nums_it;
                sum += sum_this_loop;
            }

        }

        return sum;
    }
};


int main()
{
  Solution soln;

  std::cout << soln.romanToInt("III") << std::endl;
}
