#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  long long minOperations(vector<vector<int>> &queries) {
    int n = queries.size();
    long long res = 0;
    for (int i = 0; i < n; i++) {
      long long t = 0;
      for (int j = 0; j <= 15; j++) {
        long long as = pow(4ll, j), ae = pow(4ll, j + 1) - 1, bs = queries[i][0], be = queries[i][1];
        if (bs > ae || as > be) {
          continue;
        }
        long long is = max(as, bs);
        long long ie = min(ae, be);
        t += (ie - is + 1) * (j + 1);
      }
      res += (t + 1) / 2;
    }
    return res;
  }
};
