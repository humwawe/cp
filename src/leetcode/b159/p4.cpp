#ifdef LC_LOCAL
#include<lc-util.h>
#endif


#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>;

class Solution {
public:
  vector<int> kthSmallest(vector<int> &par, vector<int> &vals, vector<vector<int>> &queries) {
    int n = par.size();
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
      g[par[i]].push_back(i);
    }

    int m = queries.size();
    vector<vector<pair<int, int>>> qs(n);
    for (int i = 0; i < m; i++) {
      int x = queries[i][0], k = queries[i][1];
      qs[x].emplace_back(k, i);
    }

    vector<int> ans(m, -1);
    // 必须返回指针，直接返回 ordered_set 会重新 build 一个新的有序集合，导致超时
    function<ordered_set *(int, int)> dfs = [&](int x, int xor_) -> ordered_set *{
      xor_ ^= vals[x];
      ordered_set *st = new ordered_set();
      st->insert(xor_);
      for (int y: g[x]) {
        ordered_set *st_y = dfs(y, xor_);
        // 启发式合并：小集合并入大集合
        if (st_y->size() > st->size()) {
          swap(st, st_y);
        }
        for (int v: *st_y) {
          st->insert(v);
        }
        delete st_y;
      }

      for (auto &[k, idx]: qs[x]) {
        if (k - 1 < st->size()) {
          ans[idx] = *st->find_by_order(k - 1);
        }
      }
      return st;
    };

    ordered_set *st = dfs(0, 0);
    delete st;

    return ans;
  }
};
