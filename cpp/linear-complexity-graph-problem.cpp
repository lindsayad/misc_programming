#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class FindCriticalPoint {
  int _counter;
  std::vector<int> _preorder;
  std::vector<int> _low;

  void dfs(const vector<vector<int>> &graph, int src, int parent,
           vector<vector<int>> &result) {
    _preorder[src] = _counter++;
    _low[src] = _preorder[src];

    const auto &neighbors = graph[src];

    for (const auto neighbor : neighbors) {
      if (_preorder[neighbor] == -1) {
        // Not visited yet

        dfs(graph, neighbor, src, result);

        _low[src] = min(_low[src], _low[neighbor]);

        if (_low[neighbor] == _preorder[neighbor])
          result.push_back(std::vector<int>({src, neighbor}));
      } else if (neighbor != parent) {
        _low[src] = min(_low[src], _preorder[neighbor]);
      }
    }
  }

public:
  vector<vector<int>>
  getCriticalConnections(int n, const vector<vector<int>> &connections) {
    vector<vector<int>> result;

    vector<vector<int>> graph(n);

    for (const auto &connection_vector : connections) {

      assert(connection_vector.size() == 2);
      graph[connection_vector[0]].push_back(connection_vector[1]);
      graph[connection_vector[1]].push_back(connection_vector[0]);
    }

    _counter = 0;
    _preorder.resize(n, -1), _low.resize(n, -1);

    for (int i = 0; i < n; ++i)
      if (_preorder[i] == -1)
        dfs(graph, i, i, result);

    return result;
  }
};

int main() {
  FindCriticalPoint fcp;

  vector<vector<int>> test = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};

  auto result = fcp.getCriticalConnections(4, test);

  for (const auto &pair : result) {
    assert(pair.size() == 2);
    std::cout << "critical connection between " << pair[0] << " and " << pair[1]
              << ".\n";
  }
}
