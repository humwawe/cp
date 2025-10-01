#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long numOfSubsequences(string s) {
    int n = s.size();

    int f[n + 2], g[n + 2];
    f[0] = g[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
      f[i] = f[i - 1];
      if (s[i - 1] == 'L') f[i]++;
    }
    for (int i = n; i > 0; i--) {
      g[i] = g[i + 1];
      if (s[i - 1] == 'T') g[i]++;
    }

    long long base = 0, lc = 0, ct = 0;
    for (int i = 1; i <= n; i++)
      if (s[i - 1] == 'C') {
        base += 1LL * f[i - 1] * g[i + 1];
        lc += f[i - 1];
        ct += g[i + 1];
      }

    long long ans = base + max(lc, ct);
    for (int i = 1; i <= n; i++) {
      ans = max(ans, base + 1LL * f[i] * g[i + 1]);
    }
    return ans;
  }
};
