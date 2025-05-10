#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int maxWeight(int n, vector<vector<int>> &edges, int k, int t) {
    vector<vector<array<int, 2>>> g(n);
    vector<int> deg(n);
    for (auto &e: edges) {
      if (e[2] < t) {
        g[e[0]].push_back({e[1], e[2]});
        deg[e[1]]++;
      }
    }

    vector dp(n, vector<bitset<600>>(k + 1));
    queue<int> que;
    for (int i = 0; i < n; i++) {
      dp[i][0][0] = 1;
      if (deg[i] == 0) {
        que.push(i);
      }
    }

    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (auto &[v, w]: g[u]) {
        for (int i = 0; i < k; i++) {
          dp[v][i + 1] |= dp[u][i] << w;
        }

        if (--deg[v] == 0) {
          que.push(v);
        }
      }
    }
    int res{-1};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < t; j++) {
        if (dp[i][k][j]) {
          res = max(res, j);
        }
      }
    }
    return res;
  }
};
