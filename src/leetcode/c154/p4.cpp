#ifdef LC_LOCAL
#include<lc-util.h>
#endif


//[0, n)
template<typename T>
struct Fenwick {
  int n{};
  vector<T> a;

  Fenwick(int n_ = 0) {
    init(n_);
  }

  void init(int n_) {
    n = n_;
    a.assign(n, T{});
  }

  void add(int p, const T v) {
    assert(0 <= p && p < n);

    for (int i = p + 1; i <= n; i += i & -i) {
      a[i - 1] = a[i - 1] + v;
    }
  }

  T _sum(int x) {
    T res{};
    for (int i = x; i > 0; i -= i & -i) {
      res = res + a[i - 1];
    }
    return res;
  }

  T rangeSum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return _sum(r) - _sum(l);
  }

  Fenwick(vector<T> _a) {
    init(_a.size());

    for (int i = 0; i < n; i++) {
      a[i] += _a[i];
      int j = i + ((i + 1) & -(i + 1));
      if (j < n) {
        a[j] += a[i];
      }
    }
  }

  void set(int i, T x) {
    add(i, x - get(i));
  }

  T get(int i) {
    return rangeSum(i, i + 1);
  }
};


class Solution {
public:
  vector<int> treeQueries(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
    vector<vector<int>> g(n);
    for (auto &e: edges) {
      g[e[0] - 1].push_back(e[1] - 1);
      g[e[1] - 1].push_back(e[0] - 1);
    }
    vector<int> in(n), out(n);
    int time = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
      in[u] = time++;
      for (auto v: g[u]) {
        if (v == p) continue;
        dfs(v, u);
      }
      out[u] = time;
    };
    dfs(0, 0);
    vector<int> wei(n);
    Fenwick<int> fen(n + 1);
    auto update = [&](int x, int y, int w) {
      if (in[x] > in[y]) {
        y = x;
      }
      int d = w - wei[y];
      wei[y] = w;
      fen.add(in[y], d);
      fen.add(out[y], -d);
    };
    for (auto &e: edges) {
      update(e[0] - 1, e[1] - 1, e[2]);
    }
    vector<int> res;
    for (auto &q: queries) {
      if (q[0] == 1) {
        update(q[1] - 1, q[2] - 1, q[3]);
      } else {
        res.push_back(fen.rangeSum(0, in[q[1] - 1] + 1));
      }
    }
    return res;
  }
};
