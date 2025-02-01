#include <lc-util.h>

class Solution {
public:
  string minCostGoodCaption(string caption) {
    int n = caption.size();
    if (n <= 2) {
      return "";
    }
    ranges::reverse(caption);
    int inf = 1e8;
    vector dp(n, vector<int>(26, inf));
    vector pre(n, vector<array<int, 2>>(26));
    for (int i = 0; i < 26; i++) {
      int t = 0;
      for (int j = 0; j < 3; j++) {
        t += abs(caption[j] - 'a' - i);
      }
      dp[2][i] = t;
      pre[2][i] = {1, i};
    }

    for (int i = 3; i < n; i++) {
      int m = inf;
      int pc = -1;
      for (int k = 0; k < 26; k++) {
        if (dp[i - 3][k] < m) {
          m = dp[i - 3][k];
          pc = k;
        }
      }

      for (int j = 0; j < 26; j++) {
        if (dp[i][j] > dp[i - 1][j] + abs(caption[i] - 'a' - j)) {
          dp[i][j] = dp[i - 1][j] + abs(caption[i] - 'a' - j);
          pre[i][j] = {0, j};
        }
        int t = 0;
        for (int k = 0; k < 3; k++) {
          t += abs(caption[i - k] - 'a' - j);
        }

        if (dp[i][j] > m + t || dp[i][j] == m + t && pc < j) {
          dp[i][j] = m + t;
          pre[i][j] = {1, pc};
        }
      }
    }

    int m = inf;
    int pc = -1;
    for (int i = 0; i < 26; i++) {
      if (dp[n - 1][i] < m) {
        m = dp[n - 1][i];
        pc = i;
      }
    }
    string res{};
    while (res.length() < n) {
      auto [t, c] = pre[n - 1 - res.length()][pc];
      if (t == 0) {
        res += 'a' + pc;
        pc = c;
      } else {
        string x(3, 'a' + pc);
        res += x;
        pc = c;
      }
    }
    return res;
  }
};

