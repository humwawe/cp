#include<lc-util.h>

class Solution {
public:
  int minCost(vector<int> &nums) {
    int n = nums.size();
    if (n <= 2) {
      return ranges::max(nums);
    }
    int inf = 1e9;
    vector dp(n, vector(n, inf));

    dp[2][0] = max(nums[1], nums[2]);
    dp[2][1] = max(nums[0], nums[2]);
    dp[2][2] = max(nums[0], nums[1]);

    for (int i = 4; i < n; i += 2) {
      for (int j = 0; j <= i - 2; j++) {
        dp[i][j] = dp[i - 2][j] + max(nums[i], nums[i - 1]);
        dp[i][i - 1] = min(dp[i][i - 1], dp[i - 2][j] + max(nums[j], nums[i]));
        dp[i][i] = min(dp[i][i], dp[i - 2][j] + max(nums[j], nums[i - 1]));
      }
    }
    int res{inf};
    if (n % 2 == 0) {
      for (int i = 0; i <= n - 2; i++) {
        res = min(res, dp[n - 2][i] + max(nums[i], nums[n - 1]));
      }
      return res;
    }
    for (int i = 0; i <= n - 1; i++) {
      res = min(res, dp[n - 1][i] + nums[i]);
    }
    return res;
  }
};
