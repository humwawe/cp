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
  int numberOfComponents(vector<vector<int>> &properties, int k) {
    int n = properties.size();
    DSU dsu(n);
    for (int i = 0; i < n; ++i) {
      vector<int> vis(101);
      for (int j = 0; j < properties[i].size(); ++j) {
        vis[properties[i][j]] = 1;
      }
      for (int j = i + 1; j < n; ++j) {
        int t = 0;
        unordered_set<int> st;
        for (int l: properties[j]) {
          st.insert(l);
        }
        for (int l: st) {
          if (vis[l]) {
            t++;
          }
        }
        if (t >= k) {
          dsu.merge(i, j);
        }
      }
    }
    int res{};
    for (int i = 0; i < n; ++i) {
      if (dsu.find(i) == i) {
        res++;
      }
    }
    return res;
  }
};
