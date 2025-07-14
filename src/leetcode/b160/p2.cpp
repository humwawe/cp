#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long minCost(int m, int n, vector<vector<int>> &waitCost) {
    vector f(m + 1, vector(n + 1, LLONG_MAX));
    f[0][1] = -waitCost[0][0];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        f[i + 1][j + 1] = min(f[i + 1][j], f[i][j + 1]) + waitCost[i][j] + 1LL * (i + 1) * (j + 1);
      }
    }
    return f[m][n] - waitCost[m - 1][n - 1];
  }
};
