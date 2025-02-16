#include<lc-util.h>

class Solution {
  vector<int> xlsh;
  vector<int> ylsh;
  int n{};
  int m{};

  void Lsh(vector<int> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
  }

  struct Node {
    int sum = 0;
    int len = 0;
    int cnt = 0;

    void Update() {
      if (cnt) {
        sum = len;
      } else {
        sum = 0;
      }
    }
  };

  vector<Node> xds;

  void Update(int p) {
    if (xds[p].cnt) {
      xds[p].sum = xds[p].len;
    } else {
      xds[p].sum = xds[p << 1].sum + xds[p << 1 | 1].sum;
    }
  }

  void Build(int p, int l, int r) {
    xds[p].len = xlsh[r + 1] - xlsh[l];
    if (l < r) {
      int mid = (l + r) >> 1;
      Build(p << 1, l, mid);
      Build(p << 1 | 1, mid + 1, r);
    }
  }

  void Modify(int l, int r, int v, int p, int lp, int rp) {
    if (r < lp || rp < l) {
      return;
    }
    if (l <= lp && rp <= r) {
      xds[p].cnt += v;
      // xds[p].Update();
      if (lp == rp) {
        xds[p].Update();
      } else {
        Update(p);
      }
      return;
    }
    int mid = (lp + rp) >> 1;
    Modify(l, r, v, p << 1, lp, mid);
    Modify(l, r, v, p << 1 | 1, mid + 1, rp);
    Update(p);
  }

  vector<vector<tuple<int, int, int>>> queries;

  vector<long long> areas;

  void GenAreas() {
    for (int i = 0; i < m - 1; i++) {
      for (const auto &[l, r, v]: queries[i]) {
        Modify(l, r, v, 1, 0, n - 2);
      }
      areas[i] = (long long) xds[1].sum * (ylsh[i + 1] - ylsh[i]);
    }
  }

public:
  double separateSquares(vector<vector<int>> &squares) {
    xlsh.clear();
    ylsh.clear();
    for (const auto &sq: squares) {
      auto x = sq[0], y = sq[1], l = sq[2];
      xlsh.push_back(x);
      xlsh.push_back(x + l);
      ylsh.push_back(y);
      ylsh.push_back(y + l);
    }
    Lsh(xlsh);
    Lsh(ylsh);
    n = xlsh.size();
    m = ylsh.size();
    xds.assign(n * 4 + 1, {});
    areas.assign(m - 1, 0);
    queries.assign(m, {});
    Build(1, 0, n - 2);
    for (const auto &sq: squares) {
      auto x = sq[0], y = sq[1], a = sq[2];
      auto x1 = ranges::lower_bound(xlsh, x) - xlsh.begin();
      auto x2 = ranges::lower_bound(xlsh, x + a) - xlsh.begin();
      auto y1 = ranges::lower_bound(ylsh, y) - ylsh.begin();
      auto y2 = ranges::lower_bound(ylsh, y + a) - ylsh.begin();
      queries[y1].emplace_back(x1, x2 - 1, 1);
      queries[y2].emplace_back(x1, x2 - 1, -1);
    }
    GenAreas();
    long long sum = reduce(areas.begin(), areas.end(), 0ll);
    long long cur = 0;
    for (int i = 0; i < m - 1; i++) {
      long long next = cur + areas[i];
      if (next * 2 >= sum) {
        return ylsh[i] + (ylsh[i + 1] - ylsh[i]) * (sum / 2.0 - cur) / (next - cur);
      }
      cur = next;
    }
    return ylsh[m - 1];
  }
};
