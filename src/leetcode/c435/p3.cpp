#include<lc-util.h>

class Solution {
public:
  int minimumIncrements(vector<int> &nums, vector<int> &target) {
    long long n = nums.size();
    long long m = target.size();
    long long lim = 1 << m;
    vector a(n, vector(lim, 0ll));
    for (int j = 0; j < lim; j++) {
      long t = 1;
      for (int i = 0; i < m; i++) {
        if (j >> i & 1) t = lcm(t, target[i]);
      }
      for (int i = 0; i < n; i++) {
        a[i][j] = (t - nums[i] % t) % t;
        cout << a[i][j] << " ";
      }
    }

    long inf = 1e12;
    vector dp(n, vector<long long>(lim, inf));
    for (int i = 0; i < lim; i++) {
      dp[0][i] = a[0][i];
    }

    for (int i = 1; i < n; i++) {
      for (int j = 0; j < lim; j++) {
        for (int k = 0; k < lim; k++) {
          if ((j & k) == 0) {
            dp[i][j | k] = min(dp[i][j | k], dp[i - 1][j] + a[i][k]);
          }
        }
      }
    }
    return dp[n - 1][lim - 1];
  }
};
