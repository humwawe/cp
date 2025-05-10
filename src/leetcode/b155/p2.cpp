#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  vector<int> baseUnitConversions(vector<vector<int>> &conversions) {
    int n = conversions.size() + 1;
    vector<vector<array<int, 2>>> g(n);
    for (vector<int> con: conversions) {
      g[con[0]].push_back({con[1], con[2]});
    }
    vector<int> res(n);
    res[0] = 1;
    int mod{1000000007};
    function<void(int, int)> dfs = [&](int u, int p) {
      for (auto [v, w]: g[u]) {
        if (v == p) continue;
        res[v] = (long long) res[u] * w % mod;
        dfs(v, u);
      }
    };
    dfs(0, 0);
    return res;
  }
};
