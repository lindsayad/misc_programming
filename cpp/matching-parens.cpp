#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
        enum class BraceType
        {
            PAREN,
            CURLY,
            SQUARE

        };
        enum class Side
        {
            LEFT,
            RIGHT
        };

    struct Brace
    {
        BraceType b_type;
        Side b_side;

        Brace(const char c)
        {
            switch (c)
            {
                case '{':
                    b_type = BraceType::CURLY;
                    b_side = Side::LEFT;
                    break;

                case '(':
                    b_type = BraceType::PAREN;
                    b_side = Side::LEFT;
                    break;

                case '[':
                    b_type = BraceType::SQUARE;
                    b_side = Side::LEFT;
                    break;

                case '}':
                    b_type = BraceType::CURLY;
                    b_side = Side::RIGHT;
                    break;

                case ')':
                    b_type = BraceType::PAREN;
                    b_side = Side::RIGHT;
                    break;

                case ']':
                    b_type = BraceType::SQUARE;
                    b_side = Side::RIGHT;
                    break;
            }
        }
    };

    bool closesCorrectly(const Brace & lhs, const Brace & rhs)
    {
        if (lhs.b_type == rhs.b_type && lhs.b_side == Side::LEFT && rhs.b_side == Side::RIGHT)
            return true;
        else
            return false;
    }

    bool isValid(string s) {

        if (s.empty())
            return true;

        vector<Brace> braces;

        for (const auto character : s)
        {
            const Brace brace(character);

            if (brace.b_side == Side::LEFT)
                braces.push_back(brace);

            else
            {
                // Did we get a right bracket to start?
                if (braces.empty())
                    return false;

                auto it = braces.end() - 1;

                if (closesCorrectly(*it, brace))
                    braces.erase(it);
                else
                    return false;
            }
        }

        return true;
    }
};

int main()
{
  Solution soln;
  std::cout << soln.isValid("()") << std::endl;
}
