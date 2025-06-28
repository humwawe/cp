#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minOperations(string word1, string word2) {
    int n = word1.size();

    // 计算从下标 l 到 r 的子串的最少操作次数
    // rev 表示一开始要不要反转
    auto calc = [&](int l, int r, bool rev) {
      int len = r - l + 1;
      string s = word1.substr(l, len);
      if (rev) {
        ranges::reverse(s);
      }
      string goal = word2.substr(l, len);

      // 统计每种字母对的出现次数
      typedef pair<int, int> pii;
      unordered_map<int, unordered_map<int, pii>> cnt;
      for (int i = 0; i < len; i++) {
        int x = s[i] - 'a', y = goal[i] - 'a';
        if (x < y) cnt[x][y].first++;
        else if (x > y) cnt[y][x].second++;
      }

      // 最小操作次数，就是每种字母对的答案加起来
      int ret = 0;
      for (auto &p1: cnt)
        for (auto &p2: p1.second)
          ret += max(p2.second.first, p2.second.second);
      return ret;
    };

    const int INF = 1e9;
    vector<int> f(n + 1);
    vector g(n + 1, vector(n + 1, 0));

    // 预处理每个子串的最小操作次数
    for (int i = 1; i <= n; i++)
      for (int j = i; j <= n; j++)
        g[i][j] = min(calc(i - 1, j - 1, false), calc(i - 1, j - 1, true) + 1);

    // 套 DP 方程
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
      f[i] = INF;
      for (int j = i - 1; j >= 0; j--) {
        f[i] = min(f[i], f[j] + g[j + 1][i]);
      }
    }
    return f[n];
  }
};
