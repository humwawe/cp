#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  bool check(char a, char b) {
    int d = abs(a - b);
    return d == 1 || d == 25;
  }

  string lexicographicallySmallestString(string s) {
    int n = s.size();
    vector f(n, vector<char>(n, false));

    for (int len = 2; len <= n; len += 2) {
      for (int i = 0; i + len <= n; i++) {
        int j = i + len - 1;

        if (len == 2 && check(s[i], s[j])) {
          f[i][j] = true;
        }
        if (len > 2) {
          for (int k = i + 1; k <= j - 1; k += 2) {
            if (f[i][k] && f[k + 1][j]) {
              f[i][j] = true;
            }
          }
        }
        if (len > 2 && check(s[i], s[j]) && f[i + 1][j - 1]) {
          f[i][j] = true;
        }
      }
    }

    vector<string> dp(n + 1);
    for (int i = n - 1; i >= 0; --i) {
      string best = s.substr(i, 1) + dp[i + 1];
      for (int m = i + 1; m < n; ++m) {
        if (f[i][m]) {
          string cand = dp[m + 1];
          if (cand < best) best.swap(cand);
        }
      }
      dp[i] = best;
    }
    return dp[0];
  }
};
