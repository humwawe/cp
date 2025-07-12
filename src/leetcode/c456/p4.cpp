#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxStability(int n, vector<vector<int>> &edges, int K) {
    // 并查集模板
    int root[n];
    auto findroot = [&](this auto &&findroot, int x) -> int {
      if (root[x] != x) root[x] = findroot(root[x]);
      return root[x];
    };

    int mn = 1e9;
    for (int i = 0; i < n; i++) root[i] = i;
    // 先看看必须要选的边会不会形成环
    for (auto &e: edges)
      if (e[3]) {
        mn = min(mn, e[2]);
        int x = findroot(e[0]), y = findroot(e[1]);
        if (x == y) return -1;
        root[x] = y;
      }

    // 检查是不是只有一个连通块
    auto conn = [&]() {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        if (findroot(i) == i) cnt++;
        if (cnt > 1) return false;
      }
      return true;
    };

    // 再看看把所有边连起来，是不是至少能连通
    for (auto &e: edges) {
      int x = findroot(e[0]), y = findroot(e[1]);
      if (x != y) root[x] = y;
    }
    if (!conn()) return -1;

    // 检查答案是否至少为 lim
    auto check = [&](int lim) {
      for (int i = 0; i < n; i++) root[i] = i;
      // 先把免费的边连起来
      for (auto &e: edges)
        if (e[2] >= lim) {
          int x = findroot(e[0]), y = findroot(e[1]);
          if (x != y) root[x] = y;
        }
      int rem = K;
      // 如果一条“收费”边能连接两个不同的连通块，就连它
      for (auto &e: edges)
        if (e[2] * 2 >= lim && rem > 0) {
          int x = findroot(e[0]), y = findroot(e[1]);
          if (x != y) root[x] = y, rem--;
        }
      return conn();
    };

    // 二分答案
    int head = 1, tail = mn;
    while (head < tail) {
      int mid = (head + tail + 1) >> 1;
      if (check(mid)) head = mid;
      else tail = mid - 1;
    }
    return head;
  }
};
