#include <cassert>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class FindCriticalPoint {
  class Graph {
  public:
    int v;
    unordered_map<int, unordered_set<int>> connections;

    Graph(int v_in) : v(v_in) {}

    void addConnection(int u, int v) { connections[u].insert(v); }

    void removeConnection(int u, int v) { connections[u].erase(v); }
  };

  int getConnectedComponents(const Graph &graph, int n) {
    int num_components = 0;

    // This list keeps track of whether we've examined the connections stemming
    // off a given node
    std::vector<bool> visited(n, false);

    std::list<int> queue;

    for (int i = 0; i < n; ++i) {
      if (!visited[i]) {
        queue.push_back(i);
        ++num_components;
      }

      // If the network is sound then we will visit all the nodes the first time
      // through the below while loop
      while (!queue.empty()) {
        int node = queue.front();
        queue.pop_front();
        if (!visited[node]) {
          auto it = graph.connections.find(node);
          assert(it != graph.connections.end());

          const auto &connection_set = it->second;

          for (const auto connected_node : connection_set)
            if (!visited[connected_node])
              queue.push_back(connected_node);
        }
        visited[node] = true;
      }
    }

    return num_components;
  }

public:
  vector<vector<int>>
  getCriticalConnections(int n, const vector<vector<int>> &connections) {
    vector<vector<int>> result;

    Graph graph(n);

    for (const auto &connection_vector : connections) {
      assert(connection_vector.size() == 2);
      graph.addConnection(connection_vector[0], connection_vector[1]);
      graph.addConnection(connection_vector[1], connection_vector[0]);
    }

    for (const auto &conn : connections) {
      assert(conn.size() == 2);
      graph.removeConnection(conn[0], conn[1]);
      graph.removeConnection(conn[1], conn[0]);

      auto num_connected_components = getConnectedComponents(graph, n);

      if (num_connected_components > 1)
        result.push_back(conn);

      graph.addConnection(conn[0], conn[1]);
      graph.addConnection(conn[1], conn[0]);
    }

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
