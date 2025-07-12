#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minXor(vector<int> &nums, int k) {
    int n = nums.size();
    long long inf = 1e18;
    vector<long long> g(n + 1);
    g[0] = 0;
    for (int i = 1; i <= n; i++) {
      g[i] = g[i - 1] ^ nums[i - 1];
    }

    vector f(n + 1, vector(k + 1, inf));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= k; j++) {
        for (int ii = 0; ii < i; ii++) {
          f[i][j] = min(f[i][j], max(f[ii][j - 1], g[i] ^ g[ii]));
        }
      }
    }
    return f[n][k];
  }
};
