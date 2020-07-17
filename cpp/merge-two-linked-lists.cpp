#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  static ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    auto *l1_current = l1;
    auto *l2_current = l2;
    vector<ListNode *> sorted;

    while (l1_current || l2_current) {
      if (!l2_current || l1_current->val < l2_current->val) {
        sorted.push_back(l1_current);
        l1_current = l1_current->next;
      } else {
        sorted.push_back(l2_current);
        l2_current = l2_current->next;
      }
    }

    if (sorted.empty())
      return nullptr;

    for (auto it = sorted.begin();; ++it) {
      if (it + 1 != sorted.end())
        (*it)->next = *(it + 1);
      else {
        (*it)->next = nullptr;
        break;
      }
    }

    return sorted.front();
  }
};

int main() {
  ListNode *l1 = nullptr;
  ListNode *l2 = nullptr;

  Solution::mergeTwoLists(l1, l2);
}
