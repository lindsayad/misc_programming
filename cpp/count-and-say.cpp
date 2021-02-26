#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if (n == 0)
            return "";

        int i = 1;

        string result = "1";

        while (i++ < n)
        {
            result = generate(result);
        }

        return result;
    }

    string generate(const string & input)
    {
        assert(!input.empty());

        vector<pair<int, int>> seq_element_counts(1, make_pair(input[0] - '0', 1));
        auto vec_it = seq_element_counts.begin();

        for (auto it = input.begin() + 1; it != input.end(); ++it)
        {
          if ((*it - '0') == vec_it->first)
                ++(vec_it->second);
            else
            {
                ++vec_it;
                assert(vec_it == seq_element_counts.end());
                seq_element_counts.insert(vec_it, make_pair((*it) - '0', 1));
            }
        }

        string result;

        for (const auto & pair : seq_element_counts)
        {
          std::string count = std::to_string(pair.second);
          std::string element = std::to_string(pair.first);
          result.insert(result.end(), count.begin(), count.end());
          result.insert(result.end(), element.begin(), element.end());
        }

        std::cout << result << endl;

        return result;
    }
};

int main()
{
  Solution soln;

  std::cout << soln.countAndSay(4) << std::endl;
}
