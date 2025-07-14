#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minTime(int n, vector<vector<int>> &edges, int K) {
    int root[n];
    // 求并查集的根
    auto findroot = [&](this auto &&findroot, int x) -> int {
      if (root[x] != x) root[x] = findroot(root[x]);
      return root[x];
    };

    // 检查将所有时间大于 lim 的边连起来以后，是否至少有 K 个连通块
    auto check = [&](int lim) {
      for (int i = 0; i < n; i++) root[i] = i;
      for (auto &edge: edges)
        if (edge[2] > lim) {
          int x = findroot(edge[0]), y = findroot(edge[1]);
          if (x != y) root[x] = y;
        }
      int cnt = 0;
      for (int i = 0; i < n; i++) if (findroot(i) == i) cnt++;
      return cnt >= K;
    };

    // 二分答案
    int head = 0, tail = 0;
    for (auto &edge: edges) tail = max(tail, edge[2]);
    while (head < tail) {
      int mid = (head + tail) >> 1;
      if (check(mid)) tail = mid;
      else head = mid + 1;
    }
    return head;
  }
};

