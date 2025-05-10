#ifdef LC_LOCAL
#include<lc-util.h>
#endif

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
  int minOperations(vector<int> &nums) {
    int n = nums.size();
    map<int, vector<int>> mp;
    Fenwick<int> fen(n);
    for (int i = 0; i < n; i++) {
      if (nums[i] == 0) {
        fen.add(i, 1);
      } else {
        mp[nums[i]].push_back(i);
      }
    }

    int res{};
    for (auto &[k, v]: mp) {
      for (int i = 0; i < v.size();) {
        int j = i;
        while (j + 1 < v.size() && fen.rangeSum(v[i], v[j + 1] + 1) == 0) {
          j++;
        }
        res++;
        i = j + 1;
      }
      for (int i: v) {
        fen.add(i, 1);
      }
    }
    return res;
  }
};

