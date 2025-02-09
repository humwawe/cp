#include<lc-util.h>


class Solution {
public:
  long long countSubstrings(string s) {
    int n = s.size();
    long long res{};
    for (int v = 1; v < 10; v++) {
      vector<long long> dp(v);
      for (int i = 0; i < n; i++) {
        vector<long long> ndp(v);
        ndp[(s[i] - '0') % v] = 1;

        for (int j = 0; j < v; j++) {
          ndp[(j * 10 + s[i] - '0') % v] += dp[j];
        }

        if (s[i] - '0' == v) {
          res += ndp[0];
        }
        dp = move(ndp);
      }
    }
    return res;
  }
};
