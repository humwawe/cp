#ifdef LC_LOCAL
#include<lc-util.h>
#endif


template<class Info>
struct SegmentTree {
  int n;
  vector<Info> info;

  SegmentTree() : n(0) {
  }

  SegmentTree(int n_, Info v_ = Info()) {
    init(n_, v_);
  }

  template<class T>
  SegmentTree(vector<T> init_) {
    init(init_);
  }

  void init(int n_, Info v_ = Info()) {
    init(vector(n_, v_));
  }

  template<class T>
  void init(vector<T> init_) {
    n = init_.size();
    info.assign(4 << __lg(n), Info());
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (r - l == 1) {
        info[p] = init_[l];
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m, r);
      pull(p);
    };
    build(1, 0, n);
  }

  void pull(int p) {
    info[p] = info[2 * p] + info[2 * p + 1];
  }

  void modify(int p, int l, int r, int x, const Info &v) {
    if (r - l == 1) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    if (x < m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m, r, x, v);
    }
    pull(p);
  }

  void modify(int p, const Info &v) {
    modify(1, 0, n, p, v);
  }

  Info rangeQuery(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
  }

  Info rangeQuery(int l, int r) {
    return rangeQuery(1, 0, n, l, r);
  }
};

using i64 = int;
constexpr i64 inf = 1E9 + 5;
int mod{};

struct Info {
  i64 x;

  // vector<i64> cnt;
  array<int, 5> cnt;

  Info(i64 x_ = inf) : x(x_), cnt{} {
    if (x_ != inf) {
      x = x_ % mod;
      cnt[x % mod] = 1;
    }
  }
};

Info operator+(const Info &a, const Info &b) {
  Info c;
  if (a.x == inf) {
    return b;
  } else if (b.x == inf) {
    return a;
  }
  c.x = (a.x * b.x) % mod;
  for (int i = 0; i < mod; i++) {
    c.cnt[i] = a.cnt[i];
  }
  for (int i = 0; i < mod; i++) {
    c.cnt[a.x * i % mod] += b.cnt[i];
  }
  return c;
}

class Solution {
public:
  vector<int> resultArray(vector<int> &nums, int k, vector<vector<int>> &queries) {
    mod = k;
    int n = nums.size();
    SegmentTree<Info> seg(nums);
    vector<int> res;
    for (auto &q: queries) {
      seg.modify(q[0], q[1]);
      Info info = seg.rangeQuery(q[2], n);
      res.push_back(info.cnt[q[3]]);
    }
    return res;
  }
};


int main() {
  Solution s;
  vector<int> nums{9, 3};
  vector<vector<int>> q{{0, 17, 1, 0}};
  auto result_array = s.resultArray(nums, 2, q);
  for (auto &x: result_array) {
    cout << x << " ";
  }
}
