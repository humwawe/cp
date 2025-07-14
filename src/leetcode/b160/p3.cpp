#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minTime(int n, vector<vector<int>> &edges) {
    vector<vector<tuple<int, int, int>>> g(n);
    for (auto &e: edges) {
      g[e[0]].emplace_back(e[1], e[2], e[3]);
    }

    vector dis(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dis[0] = 0;
    pq.emplace(0, 0);

    while (!pq.empty()) {
      auto [dx, x] = pq.top();
      pq.pop();
      if (dx > dis[x]) {
        continue;
      }
      if (x == n - 1) {
        return dx;
      }
      for (auto &[y, start, end]: g[x]) {
        int nd = max(dx, start) + 1;
        if (nd - 1 <= end && nd < dis[y]) {
          dis[y] = nd;
          pq.emplace(nd, y);
        }
      }
    }
    return -1;
  }
};
