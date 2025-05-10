#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long subtreeInversionSum(vector<vector<int>> &edges, vector<int> &nums, int k) {
    int n = nums.size();
    vector<vector<int>> g(n);
    for (auto &e: edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }
    const long long inf = 1e18;

    vector mn(n, vector(k + 1, inf));
    vector mx(n, vector<long long>(k + 1, -inf));

    function<void(int, int)> dfs = [&](int u, int p) {
      for (int i = 0; i <= k; ++i)
        mx[u][i] = mn[u][i] = nums[u];

      for (int v: g[u]) {
        if (v == p) {
          continue;
        }
        dfs(v, u);
        for (int i = 1; i <= k; ++i) {
          mn[v][i] = min(mn[v][i], mn[v][i - 1]);
          mx[v][i] = max(mx[v][i], mx[v][i - 1]);
          if (i >= 2) {
            if (mn[v][i] != inf)
              mn[u][max(i - 1, 0)] += mn[v][i];
            if (mx[v][i] != -inf)
              mx[u][max(i - 1, 0)] += mx[v][i];
          }
        }
        mn[u][0] += min(mn[v][0], mn[v][1]);
        mx[u][0] += max(mx[v][0], mx[v][1]);
      }

      mx[u][k] = max(mx[u][0], -mn[u][0]);
      mn[u][k] = min(mn[u][k], -mx[u][0]);
    };

    dfs(0, -1);

    long long res = 0;
    for (int i = 0; i <= k; ++i)
      res = max(res, mx[0][i]);
    return res;
  }
};
