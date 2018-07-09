#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

int main() {
  set<int> s1;
  set<int> s2;

  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.insert(4);

  s2.insert(1);
  s2.insert(6);
  s2.insert(3);
  s2.insert(0);

  set<int> intersect;
  set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),
                   std::inserter(intersect,intersect.begin()));

  for (auto & element : intersect)
    cout << "Intersecting element: " << element << endl;

  return 0;
}
