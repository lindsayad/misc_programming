#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    typedef decltype(vector<int>().begin()) vec_iterator;
    string longestCommonPrefix(vector<string>& strs) {
        vector<string::const_iterator> string_iterators(strs.size());
        std::string result = "";

        if (strs.empty())
            return result;

        for (const auto & string : strs)
            if (string.empty())
                return result;

        int pos = 0;
        while (!finished(pos, strs, string_iterators))
        {
            bool all_match = true;
            auto value = *string_iterators[0];
            for (size_t i = 1; i < string_iterators.size(); ++i)
            {
                if (*string_iterators[i] != value)
                {
                    all_match = false;
                    break;
                }
            }

            if (all_match)
                result.push_back(value);
            else
                break;

            ++pos;

        }

        return result;
    }

    bool finished(int pos, const vector<string> & strs, vector<string::const_iterator> & string_iterators)
    {
        for (size_t i = 0; i < strs.size(); ++i)
        {
            auto & it = string_iterators[i];
            it = strs[i].begin() + pos;
            if (it == strs[i].end())
                return true;
        }
        return false;

    }
};

int main()
{
  Solution soln;

  vector<string> test = {"flower","flow","flight"};
  std::cout << soln.longestCommonPrefix(test) << std::endl;
}
