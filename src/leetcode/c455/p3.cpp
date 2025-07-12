#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minIncrease(int n, vector<vector<int>> &edges, vector<int> &cost) {
    vector<vector<int>> g(n);
    for (auto &e: edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }

    vector<long long> d(n);
    int res{};
    function<void(int, int)> dfs = [&](int u, int p) {
      vector<long long> tmp;
      for (auto v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
        tmp.push_back(d[v]);
      }
      long long m{};
      if (!tmp.empty()) {
        m = ranges::max(tmp);
      }
      d[u] = m + cost[u];
      for (long long v: tmp) {
        if (v != m) {
          res++;
        }
      }
    };
    dfs(0, 0);
    return res;
  }
};
