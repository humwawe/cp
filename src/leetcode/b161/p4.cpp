#ifdef LC_LOCAL
#include<lc-util.h>
#endif


#define MAXP 50
long long f[MAXP][MAXP + 1];
int g[MAXP + 1];
bool inited = false;

void init() {
  if (inited) return;
  inited = true;
  memset(f, -1, sizeof(f));
  // 预处理 1 到 50 的位深度
  for (int i = 1; i <= MAXP; i++) {
    g[i] = 0;
    for (int x = i; x > 1; x = __builtin_popcount(x)) g[i]++;
  }
}

class Solution {
public:
  long long popcountDepth(long long n, int K) {
    init();
    if (K == 0) return 1;

    // 数位 DP
    // 现在正在考虑第 pos 低位，还剩 cnt 个 1 没决定，且当前位是否 full 的方案数
    auto dp = [&](this auto &&dp, int pos, int cnt, int full) -> long long {
      if (cnt < 0) return 0;
      if (pos < 0) return cnt == 0 ? 1 : 0;
      if (!full && f[pos][cnt] >= 0) return f[pos][cnt];

      long long ret = 0;
      int R = (full ? n >> pos & 1 : 1);
      for (int i = 0; i <= R; i++) ret += dp(pos - 1, cnt - i, full && i == R ? 1 : 0);
      if (!full) f[pos][cnt] = ret;
      return ret;
    };

    long long ans = 0;
    // 枚举位深度为 K - 1 的所有数
    for (int i = 1; i <= MAXP; i++)
      if (g[i] == K - 1) {
        ans += dp(MAXP - 1, i, 1);
        // 特殊情况：1 虽然也满足有 1 个 1，但它的位深度是 0
        if (i == 1) ans--;
      }
    return ans;
  }
};
