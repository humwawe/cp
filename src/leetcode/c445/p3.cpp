#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  string smallestPalindrome(string s, int k) {
    int n = s.size();
    int m = n / 2;
    vector<int> cnt(26);
    for (int i = 0; i < m; i++) {
      cnt[s[i] - 'a']++;
    }

    auto comb = [&](int n, int m) -> int {
      m = min(m, n - m);
      long long res = 1;
      for (int i = 1; i <= m; i++) {
        res = res * (n + 1 - i) / i;
        if (res >= k) {
          // 太大了
          return k;
        }
      }
      return res;
    };

    auto perm = [&](int sz) -> int {
      long long res = 1;
      for (int c: cnt) {
        if (c == 0) {
          continue;
        }
        // 先从 sz 个里面选 c 个位置填当前字母
        res *= comb(sz, c);
        if (res >= k) {
          return k;
        }
        sz -= c;
      }
      return res;
    };

    if (perm(m) < k) {
      return "";
    }

    string left_s(m, 0);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < 26; j++) {
        if (cnt[j] == 0) {
          continue;
        }
        cnt[j]--;
        int p = perm(m - i - 1);
        if (p >= k) {
          left_s[i] = 'a' + j;
          break;
        }
        k -= p;
        cnt[j]++;
      }
    }

    string ans = left_s;
    if (n % 2) {
      ans += s[n / 2];
    }
    ranges::reverse(left_s);
    return ans + left_s;
  }
};
