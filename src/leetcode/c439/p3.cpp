#include<lc-util.h>


class Solution {
public:
  int maxSum(vector<int> &nums, int k, int m) {
    int n = nums.size();
    vector<int> sum(n + 1);
    for (int i = 0; i < n; ++i) {
      sum[i + 1] = sum[i] + nums[i];
    }
    int inf = 1e9;

    vector dp(k + 1, vector(n + 1, -inf));
    for (int i = 0; i < n + 1; i++) {
      dp[0][i] = 0;
    }
    for (int j = 1; j <= k; j++) {
      int ma = -inf;
      for (int i = 1; i <= n; i++) {
        if (i - m >= 0) {
          ma = max(ma, dp[j - 1][i - m] - sum[i - m]);
        }
        dp[j][i] = sum[i] + ma;
      }
      for (int i = 1; i <= n; i++) {
        dp[j][i] = max(dp[j][i], dp[j][i - 1]);
      }
    }
    return dp[k][n];
  }
};
