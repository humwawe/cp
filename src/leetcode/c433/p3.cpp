#include<lc-util.h>

class Solution {
public:
  long long minCost(int n, vector<vector<int>> &cost) {
    long long inf = 1e12;
    int m = 16;

    vector can(m, vector<int>(m));

    for (int i = 0; i < m; i++) {
      int x = i & 3;
      int y = (i >> 2) & 3;
      if (x != y) {
        for (int j = 0; j < m; j++) {
          int a = j & 3;
          int b = (j >> 2) & 3;
          if (a != b && a != x && b != y && ranges::max({x, y, a, b}) != 3) {
            can[i][j] = 1;
          }
        }
      }
    }
    vector dp(n + 1, vector(m, inf));
    for (int i = 0; i < m; i++) {
      dp[0][i] = 0;
    }
    for (int i = 1; i <= n / 2; i++) {
      for (int cur = 0; cur < m; cur++) {
        for (int pre = 0; pre < m; pre++) {
          if (can[pre][cur]) {
            int x = cur & 3;
            int y = (cur >> 2) & 3;

            dp[i][cur] = min(dp[i][cur], dp[i - 1][pre] + cost[i - 1][x] + cost[n - i][y]);
          }
        }
      }
    }
    return ranges::min(dp[n / 2]);
  }
};
