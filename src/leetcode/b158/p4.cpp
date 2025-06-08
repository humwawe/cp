#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int goodSubtreeSum(vector<int> &vals, vector<int> &par) {
    int n = vals.size();
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
      g[par[i]].push_back(i);
    }

    vector<int> msk(n);
    for (int i = 0; i < n; i++) {
      msk[i] = 0;
      for (int x = vals[i]; x && msk[i] >= 0; x /= 10) {
        int y = x % 10;
        if (msk[i] >> y & 1) {
          msk[i] = -1;
        } else msk[i] |= 1 << y;
      }
    }

    const long long inf = 1e18;
    const int m = 1 << 10;
    vector f(n, vector(m, -inf));
    function<void(int)> dfs = [&](int u) -> void {
      f[u][0] = 0;

      for (int v: g[u]) {
        dfs(v);
        for (int i = m - 1; i >= 0; i--) {
          for (int j = i; j > 0; j = i & (j - 1)) {
            f[u][i] = max(f[u][i], f[u][i ^ j] + f[v][j]);
          }
        }
      }

      if (msk[u] >= 0) {
        for (int i = m - 1; i >= 0; i--) {
          if ((i & msk[u]) == msk[u]) {
            f[u][i] = max(f[u][i], f[u][i ^ msk[u]] + vals[u]);
          }
        }
      }
    };

    dfs(0);

    const int mod = 1e9 + 7;
    long long res{};
    for (int i = 0; i < n; i++) {
      res = (res + ranges::max(f[i])) % mod;
    }
    return res;
  }
};
