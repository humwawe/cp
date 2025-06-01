#ifdef LC_LOCAL
#include<lc-util.h>
#endif


const int MX = 100'000;
bool np[MX + 1];

int init = []() {
  np[0] = np[1] = true;
  for (int i = 2; i <= MX; i++) {
    if (!np[i]) {
      for (int j = i; j <= MX / i; j++) {
        // 避免溢出的写法
        np[i * j] = true;
      }
    }
  }
  return 0;
}();

template<typename T, typename F>
class LazySegmentTree {
  // 注：也可以去掉 template<typename T, typename F>，改在这里定义 T 和 F
  // using T = pair<int, int>;
  // using F = pair<int, int>;

  // 懒标记初始值
  const F TODO_INIT = 0;

  struct Node {
    T val;
    F todo;
  };

  int n;
  vector<Node> tree;

  // 合并两个 val
  T merge_val(T a, T b) const {
    return max(a, b);
  }

  // 合并两个懒标记
  F merge_todo(F a, F b) const {
    return a + b;
  }

  // 把懒标记作用到 node 子树（本例为区间加）
  void apply(int node, int l, int r, F todo) {
    Node &cur = tree[node];
    // 计算 tree[node] 区间的整体变化
    cur.val += todo;
    cur.todo = merge_todo(todo, cur.todo);
  }

  // 把当前节点的懒标记下传给左右儿子
  void spread(int node, int l, int r) {
    Node &cur = tree[node];
    F todo = cur.todo;
    if (todo == TODO_INIT) {
      // 没有需要下传的信息
      return;
    }
    int m = (l + r) / 2;
    apply(node * 2, l, m, todo);
    apply(node * 2 + 1, m + 1, r, todo);
    cur.todo = TODO_INIT; // 下传完毕
  }

  // 合并左右儿子的 val 到当前节点的 val
  void maintain(int node) {
    tree[node].val = merge_val(tree[node * 2].val, tree[node * 2 + 1].val);
  }

  // 用 a 初始化线段树
  // 时间复杂度 O(n)
  void build(const vector<T> &a, int node, int l, int r) {
    Node &cur = tree[node];
    cur.todo = TODO_INIT;
    if (l == r) {
      // 叶子
      cur.val = a[l]; // 初始化叶节点的值
      return;
    }
    int m = (l + r) / 2;
    build(a, node * 2, l, m); // 初始化左子树
    build(a, node * 2 + 1, m + 1, r); // 初始化右子树
    maintain(node);
  }

  void update(int node, int l, int r, int ql, int qr, F f) {
    if (ql <= l && r <= qr) {
      // 当前子树完全在 [ql, qr] 内
      apply(node, l, r, f);
      return;
    }
    spread(node, l, r);
    int m = (l + r) / 2;
    if (ql <= m) {
      // 更新左子树
      update(node * 2, l, m, ql, qr, f);
    }
    if (qr > m) {
      // 更新右子树
      update(node * 2 + 1, m + 1, r, ql, qr, f);
    }
    maintain(node);
  }

  T query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      // 当前子树完全在 [ql, qr] 内
      return tree[node].val;
    }
    spread(node, l, r);
    int m = (l + r) / 2;
    if (qr <= m) {
      // [ql, qr] 在左子树
      return query(node * 2, l, m, ql, qr);
    }
    if (ql > m) {
      // [ql, qr] 在右子树
      return query(node * 2 + 1, m + 1, r, ql, qr);
    }
    T l_res = query(node * 2, l, m, ql, qr);
    T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
    return merge_val(l_res, r_res);
  }

public:
  // 线段树维护一个长为 n 的数组（下标从 0 到 n-1），元素初始值为 init_val
  LazySegmentTree(int n, T init_val = 0) : LazySegmentTree(vector<T>(n, init_val)) {
  }

  // 线段树维护数组 a
  LazySegmentTree(const vector<T> &a) : n(a.size()), tree(2 << bit_width(a.size() - 1)) {
    build(a, 1, 0, n - 1);
  }

  // 用 f 更新 [ql, qr] 中的每个 a[i]
  // 0 <= ql <= qr <= n-1
  // 时间复杂度 O(log n)
  void update(int ql, int qr, F f) {
    update(1, 0, n - 1, ql, qr, f);
  }

  // 返回用 merge_val 合并所有 a[i] 的计算结果，其中 i 在闭区间 [ql, qr] 中
  // 0 <= ql <= qr <= n-1
  // 时间复杂度 O(log n)
  T query(int ql, int qr) {
    return query(1, 0, n - 1, ql, qr);
  }
};

class Solution {
public:
  vector<int> maximumCount(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size();
    unordered_map<int, set<int>> pos;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      if (!np[x]) {
        pos[x].insert(i);
      }
    }

    LazySegmentTree<int, int> t(n);
    for (auto &[_, s]: pos) {
      if (s.size() > 1) {
        t.update(*s.begin(), *s.rbegin(), 1);
      }
    }

    vector<int> ans;
    for (auto &q: queries) {
      int i = q[0], v = q[1];
      int old = nums[i];
      nums[i] = v;

      // 处理旧值
      if (!np[old]) {
        auto &s = pos[old];
        if (s.size() > 1) {
          t.update(*s.begin(), *s.rbegin(), -1); // 撤销之前的区间 +1
        }
        s.erase(i);
        if (s.size() > 1) {
          t.update(*s.begin(), *s.rbegin(), 1); // 新的区间 +1
        } else if (s.empty()) {
          pos.erase(old);
        }
      }

      // 处理新值
      if (!np[v]) {
        auto &s = pos[v];
        if (s.size() > 1) {
          t.update(*s.begin(), *s.rbegin(), -1); // 撤销之前的区间 +1
        }
        s.insert(i);
        if (s.size() > 1) {
          t.update(*s.begin(), *s.rbegin(), 1); // 新的区间 +1
        }
      }

      // 整个数组的不同质数个数 + 切一刀的最大额外收益
      ans.push_back(pos.size() + t.query(0, n - 1));
    }

    return ans;
  }
};
