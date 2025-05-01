#ifdef LC_LOCAL
#include<lc-util.h>
#endif
struct DSU {
  vector<int> f, siz;

  DSU() {
  }

  DSU(int n) {
    init(n);
  }

  void init(int n) {
    f.resize(n);
    ranges::iota(f, 0);
    siz.assign(n, 1);
  }

  int find(int x) {
    while (x != f[x]) {
      x = f[x] = f[f[x]];
    }
    return x;
  }

  bool same(int x, int y) {
    return find(x) == find(y);
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return false;
    }
    siz[x] += siz[y];
    f[y] = x;
    return true;
  }

  int size(int x) {
    return siz[find(x)];
  }
};

class Solution {
public:
  vector<bool> pathExistenceQueries(int n, vector<int> &nums, int maxDiff, vector<vector<int>> &queries) {
    DSU dsu(n);
    for (int i = 1; i < n; i++) {
      if (nums[i] - nums[i - 1] <= maxDiff) {
        dsu.merge(i - 1, i);
      }
    }
    vector<bool> res;
    for (auto &q: queries) {
      res.push_back(dsu.same(q[0], q[1]));
    }
    return res;
  }
};
