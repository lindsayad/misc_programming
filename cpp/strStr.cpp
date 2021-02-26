#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty())
            return 0;

        auto needle_it = needle.begin();

        bool found = false;
        int index = 0;
        auto string_it = haystack.begin();
        for (; string_it != haystack.end() && needle_it != needle.end(); ++string_it, ++index)
        {
            if (*string_it != *needle_it)
            {
                found = false;
                // Need to reset the needle iterator, but not necessarily to the very beginning. The current iterates don't match, but what about previous iterates?
                while (needle_it != needle.begin())
                {
                  --needle_it;
                    bool sub_match = false;
                    // In order to construct a reverse iterator from a forward iterator or visa versa, you must first increment the iterator we're converting by one. This is so that make_reverse_iterator(begin) actually corresponds to rend
                    for (auto sub_needle_it = make_reverse_iterator(needle_it+1), sub_hay_it  = make_reverse_iterator(string_it+1);
                         sub_needle_it != needle.rend() && sub_hay_it != haystack.rend();
                         ++sub_needle_it, ++sub_hay_it)
                    {
                        if (*sub_needle_it == *sub_hay_it)
                            sub_match = true;
                        else
                        {
                          sub_match = false;
                          break;
                        }
                    }

                    if (sub_match)
                        ++needle_it;

                    break;
                }
            }
            else
            {
                found = true;
                ++needle_it;
            }
        }

        // If we reached the end of the haystack but we haven't reached the end of the needle, then we were unsuccessful
        if (string_it == haystack.end() && needle_it != needle.end())
            return -1;
        else if (found)
            return  index - needle.size();
        else
            return -1;

    }
};

int main()
{
  Solution soln;
  std::cout << soln.strStr("mississippi", "issip") << std::endl;
  std::cout << soln.strStr("babba", "bbb") << std::endl;
  std::cout << soln.strStr("mississippi", "pi") << std::endl;
  std::cout << soln.strStr("aaabaaabbbabaa", "babb") << std::endl;


  std::string test = "pi";
  auto pos = test.find("i");
  auto it = test.begin() + pos;
  auto new_it = it - 1;
  auto reverse_it = make_reverse_iterator(new_it);
}
