#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}

  ~ListNode()
    {
      if (next)
        delete next;
    }
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      return new ListNode;
    }

    ListNode * reverseList(ListNode * head)
    {
      ListNode * current = head;
      ListNode * next = nullptr;
      ListNode * prev = nullptr;

        while (current->next)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        current->next = prev;

        return current;
    }

  void traverseAndPrint(ListNode * head)
    {
      ListNode * current = head;
      while (current)
      {
        cout << current->val << endl;
        current = current->next;
      }
    }
};

int main()
{
  Solution soln;

  ListNode head(7);

  vector<int> vals = {2, 4, 3};

  ListNode * current = &head;
  for (const auto val : vals)
  {
    current->next = new ListNode(val);
    current = current->next;
  }

  ListNode * reversed_head = soln.reverseList(&head);

  soln.traverseAndPrint(reversed_head);
}
