#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int minTravelTime(int l, int n, int k, vector<int> &position, vector<int> &time) {
    vector<long long> sum(n);
    sum[0] = time[0];
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + time[i];
    }
    long long inf = 1e18;
    vector dp(n, vector(n, vector(k + 1, inf)));

    for (int i = 1; i < n; i++) {
      if (i - 1 <= k) {
        dp[i][0][i - 1] = 1LL * position[i] * time[0];
      }
      for (int j = 1; j < i; j++) {
        int cnt = i - j - 1;
        for (int nk = cnt; nk <= k; nk++) {
          for (int jj = 0; jj < j; jj++) {
            long long dis = position[i] - position[j];
            long long t = sum[j] - sum[jj];
            dp[i][j][nk] = min(dp[i][j][nk], dp[j][jj][nk - cnt] + dis * t);
          }
        }
      }
    }
    long long res = inf;
    for (int i = 0; i < n - 1; i++) {
      res = min(res, dp[n - 1][i][k]);
    }
    return res;
  }
};
