#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int longestPalindrome(string s, string t) {
    ranges::reverse(t);

    auto calc = [&](string &s, string &t) {
      int n = s.size(), m = t.size();

      // 求 LCP
      vector f(n + 1, vector<int>(m + 1, 0));
      for (int i = n - 1; i >= 0; i--)
        for (int j = m - 1; j >= 0; j--) {
          if (s[i] != t[j]) {
            f[i][j] = 0;
          } else {
            f[i][j] = f[i + 1][j + 1] + 1;
          }
        }

      // 预处理 LCP 的后缀 max
      vector<int> g(n);
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
          g[i] = max(g[i], f[i][j]);
        }
      }

      // 预处理 s[i] 开头的最长回文子串
      vector<int> h(n + 1);
      for (int i = 0; i < n; i++) {
        for (int l = i, r = i; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
          h[l] = max(h[l], r - l + 1);
        }
      }
      for (int i = 0; i + 1 < n; i++) {
        for (int l = i, r = i + 1; l >= 0 && r < n && s[l] == s[r]; l--, r++) {
          h[l] = max(h[l], r - l + 1);
        }
      }

      int ret{};
      // 特殊情况：t 中取空串
      for (int i = 0; i < n; i++) {
        ret = max(ret, h[i]);
      }
      // 枚举 s 里子串的前缀 s[i]..s[i + j - 1]
      for (int i = 0; i < n; i++) {
        for (int j = 1; j <= g[i]; j++) {
          ret = max(ret, j * 2 + h[i + j]);
        }
      }
      return ret;
    };

    // 两种情况的答案取最大值
    return max(calc(s, t), calc(t, s));
  }
};
