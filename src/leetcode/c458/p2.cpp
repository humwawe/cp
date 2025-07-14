#ifdef LC_LOCAL
#include<lc-util.h>
#endif


// 完整的并查集模板，见我的数据结构题单
class UnionFind {
  vector<int> fa; // 代表元

public:
  int cc; // 连通块个数

  UnionFind(int n) : fa(n), cc(n) {
    ranges::iota(fa, 0);
  }

  int find(int x) {
    if (fa[x] != x) {
      fa[x] = find(fa[x]);
    }
    return fa[x];
  }

  void merge(int from, int to) {
    int x = find(from), y = find(to);
    if (x == y) {
      return;
    }
    fa[x] = y;
    cc--;
  }
};

class Solution {
public:
  int minCost(int n, vector<vector<int>> &edges, int k) {
    if (k == n) {
      return 0;
    }
    ranges::sort(edges, [](auto &a, auto &b) { return a[2] < b[2]; });
    UnionFind u(n);
    for (auto &e: edges) {
      u.merge(e[0], e[1]);
      if (u.cc == k) {
        return e[2];
      }
    }
    return -1;
  }
};
