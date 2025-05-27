#ifdef LC_LOCAL
#include<lc-util.h>
#endif
class Solution {
public:
  void dfs(int x, const vector<int> &p, const vector<int> &f) {
  }

  int maxProfit(int n, vector<int> &present, vector<int> &future, vector<vector<int>> &hierarchy, int budget) {
    vector<vector<int>> g(n);
    for (auto &q: hierarchy) {
      g[q[0] - 1].push_back(q[1] - 1);
    }


    vector<array<int, 170>> a(n), b(n);
    function<void(int)> dfs = [&](int u) {
      vector<int> sa(budget + 1), sb(budget + 1);
      for (int v: g[u]) {
        dfs(v);
        for (int i = budget; i >= 0; --i) {
          for (int j = i; j >= 0; --j) {
            sa[i] = max(sa[i], sa[j] + a[v][i - j]);
            sb[i] = max(sb[i], sb[j] + b[v][i - j]);
          }
        }
      }

      for (int i = 0; i <= budget; ++i) {
        a[u][i] = sa[i];
        b[u][i] = sa[i];
        if (i >= present[u]) {
          a[u][i] = max(a[u][i], future[u] - present[u] + sb[i - present[u]]);
        }
        if (i >= present[u] / 2) {
          b[u][i] = max(b[u][i], future[u] - present[u] / 2 + sb[i - present[u] / 2]);
        }
      }
    };

    dfs(0);
    return a[0][budget];
  }
};
