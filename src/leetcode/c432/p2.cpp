#include <lc-util.h>

class Solution {
public:
  int maximumAmount(vector<vector<int>> &coins) {
    int n = coins.size(), m = coins[0].size();
    int inf = 1e9;
    vector dp(n + 1, vector(m + 1, array<int, 3>({-inf, -inf, -inf})));
    dp[0][1][0] = dp[1][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        int v = coins[i - 1][j - 1];
        for (int k = 0; k < 3; ++k) {
          dp[i][j][k] = max(dp[i - 1][j][k] + v, dp[i][j - 1][k] + v);
          if (v < 0 && k) {
            dp[i][j][k] = max({dp[i][j][k], dp[i - 1][j][k - 1], dp[i][j - 1][k - 1]});
          }
        }
      }
    }
    return ranges::max(dp[n][m]);
  }
};
