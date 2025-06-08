#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long maximumProfit(vector<int> &prices, int k) {
    int n = prices.size();
    long long inf = 1e18;
    vector dp(n + 1, vector<array<long long, 3>>(k + 1, {-inf, -inf, -inf}));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
      int p = prices[i - 1];
      for (int j = 0; j <= k; j++) {
        for (int t = 0; t < 3; t++) {
          dp[i][j][t] = max(dp[i][j][t], dp[i - 1][j][t]);
        }
        if (j - 1 >= 0) {
          dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][0] - p);
          dp[i][j][2] = max(dp[i][j][2], dp[i - 1][j - 1][0] + p);
        }
        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][1] + p);
        dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][2] - p);
      }
    }
    long long res{-inf};
    for (int i = 0; i <= k; i++) {
      res = max(res, dp[n][i][0]);
    }
    return res;
  }
};
