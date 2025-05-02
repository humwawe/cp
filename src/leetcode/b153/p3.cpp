#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  long long minimumCost(vector<int> &nums, vector<int> &cost, int k) {
    int n = nums.size();
    vector<long long> sn(n + 1), sc(n + 1);
    for (int i = 0; i < n; ++i) {
      sn[i + 1] = sn[i] + nums[i];
      sc[i + 1] = sc[i] + cost[i];
    }
    vector dp(n + 1, LLONG_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        long long t = sn[i] * (sc[i] - sc[j]) + k * (sc[n] - sc[j]);
        dp[i] = min(dp[i], t + dp[j]);
      }
    }
    return dp[n];
  }
};
