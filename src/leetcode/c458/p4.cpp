#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxLen(int n, vector<vector<int>> &edges, string label) {
    if (edges.size() == n * (n - 1) / 2) {
      // 完全图
      int cnt[26]{};
      for (char ch: label) {
        cnt[ch - 'a']++;
      }
      int ans = 0, odd = 0;
      for (int c: cnt) {
        ans += c - c % 2;
        odd |= c % 2;
      }
      return ans + odd;
    }

    vector<vector<int>> g(n);
    for (auto &e: edges) {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector memo(n, vector(n, vector<int>(1 << n, -1)));
    // 计算从 x 和 y 向两侧扩展，最多还能访问多少个节点（不算 x 和 y）
    auto dfs = [&](this auto &&dfs, int x, int y, int vis) -> int {
      int &res = memo[x][y][vis]; // 注意这里是引用
      if (res >= 0) {
        // 之前计算过
        return res;
      }
      res = 0;
      for (int v: g[x]) {
        if (vis >> v & 1) {
          // v 在路径中
          continue;
        }
        for (int w: g[y]) {
          if ((vis >> w & 1) == 0 && w != v && label[w] == label[v]) {
            // 保证 v < w，减少状态个数和计算量
            int r = dfs(min(v, w), max(v, w), vis | 1 << v | 1 << w);
            res = max(res, r + 2);
          }
        }
      }
      return res;
    };

    int ans = 0;
    for (int x = 0; x < n; x++) {
      // 奇回文串，x 作为回文中心
      ans = max(ans, dfs(x, x, 1 << x) + 1);
      if (ans == n) {
        return n;
      }
      // 偶回文串，x 和 x 的邻居 y 作为回文中心
      for (int y: g[x]) {
        // 保证 x < y，减少状态个数和计算量
        if (x < y && label[x] == label[y]) {
          ans = max(ans, dfs(x, y, 1 << x | 1 << y) + 2);
          if (ans == n) {
            return n;
          }
        }
      }
    }
    return ans;
  }
};
