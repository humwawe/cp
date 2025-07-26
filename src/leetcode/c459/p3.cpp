#ifdef LC_LOCAL
#include<lc-util.h>
#endif


template<typename T>
class FenwickTree {
  vector<T> tree;

public:
  // 使用下标 1 到 n
  FenwickTree(int n) : tree(n + 1) {
  }

  void update(int i, T val) {
    for (; i < tree.size(); i += i & -i) {
      tree[i] += val;
    }
  }

  T pre(int i) const {
    T res = 0;
    for (; i > 0; i &= i - 1) {
      res += tree[i];
    }
    return res;
  }

  T query(int l, int r) const {
    return pre(r) - pre(l - 1);
  }
};

class Solution {
  int pop_depth(uint64_t x) {
    int res = 0;
    while (x > 1) {
      res++;
      x = popcount(x);
    }
    return res;
  }

public:
  vector<int> popcountDepth(vector<long long> &nums, vector<vector<long long>> &queries) {
    int n = nums.size();
    vector f(6, FenwickTree<int>(n + 1));
    auto update = [&](int i, int delta) -> void {
      int d = pop_depth(nums[i]);
      f[d].update(i + 1, delta);
    };

    for (int i = 0; i < n; i++) {
      update(i, 1); // 添加
    }

    vector<int> ans;
    for (auto &q: queries) {
      if (q[0] == 1) {
        ans.push_back(f[q[3]].query(q[1] + 1, q[2] + 1));
      } else {
        int i = q[1];
        update(i, -1);
        nums[i] = q[2];
        update(i, 1);
      }
    }
    return ans;
  }
};
