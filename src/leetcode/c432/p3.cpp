#include<lc-util.h>
using i64 = long long;

class Solution {
public:
  int minMaxWeight(int n, vector<vector<int>> &edges, int threshold) {
    vector<vector<pair<int, i64>>> g(n);
    for (auto &e: edges) {
      g[e[1]].emplace_back(e[0], e[2]);
    }
    vector<i64> dist = dijkstra(g, 0);
    i64 res = ranges::max(dist);
    if (res == LONG_MAX) {
      return -1;
    }
    return res;
  }

  vector<i64> dijkstra(vector<vector<pair<int, i64>>> graph, int source) {
    int n = graph.size();
    vector<i64> dist(n, LONG_MAX);
    dist[source] = 0;
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> pq;
    vector<bool> vis(n, false);
    pq.emplace(dist[source], source);
    while (!pq.empty()) {
      i64 d = pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (vis[u]) {
        continue;
      }
      vis[u] = true;
      for (auto &[v, w]: graph[u]) {
        i64 nd = max(d, w);
        if (dist[v] > nd) {
          dist[v] = nd;
          pq.emplace(dist[v], v);
        }
      }
    }
    return dist;
  }
};
