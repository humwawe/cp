#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxProfit(int n, vector<vector<int>> &edges, vector<int> &score) {
    vector<int> pre(n);
    for (auto &e: edges) {
      pre[e[1]] |= 1 << e[0];
    }
    int lim = 1 << n;
    vector<int> dp(lim, -1);
    dp[0] = 0;
    for (int i = 0; i < lim; ++i) {
      if (dp[i] < 0) {
        continue;
      }
      for (int j = 0; j < n; ++j) {
        if ((i >> j & 1) == 0 && (i | pre[j]) == i) {
          int ni = i | 1 << j;
          dp[ni] = max(dp[ni], dp[i] + score[j] * (popcount((uint32_t) i) + 1));
        }
      }
    }
    return dp[lim - 1];
  }
};
