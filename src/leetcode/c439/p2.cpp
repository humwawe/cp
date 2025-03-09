#include <lc-util.h>

class Solution {
public:
  int longestPalindromicSubsequence(string s, int c) {
    int n = s.size();
    vector<int> tmp(n);
    for (int i = 0; i < n; i++) {
      tmp[i] = s[i] - '0';
    }
    vector memo(n, vector(n, vector<int>(c + 1, -1)));
    function<int(int, int, int)> dfs = [&](int l, int r, int k) {
      if (l == r) {
        return 1;
      }
      if (l > r) {
        return 0;
      }
      if (memo[l][r][k] != -1) {
        return memo[l][r][k];
      }

      int &res = memo[l][r][k];
      if (tmp[l] == tmp[r]) {
        res = max(res, dfs(l + 1, r - 1, k) + 2);
        return res;
      }
      res = max(res, dfs(l + 1, r, k));
      res = max(res, dfs(l, r - 1, k));
      int x = min(tmp[l], tmp[r]), y = max(tmp[l], tmp[r]);
      int t = min(y - x, x + 26 - y);
      if (k >= t) {
        res = max(res, dfs(l + 1, r - 1, k - t) + 2);
      }

      return res;
    };
    return dfs(0, n - 1, c);
  }
};
