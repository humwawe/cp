#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  vector<int> subarrayMajority(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size(), m = queries.size();

    unordered_map<int, int> cnt;
    int max_cnt = 0, min_val = 0;

    // 添加元素 x
    auto add = [&](int x) {
      int c = ++cnt[x];
      if (c > max_cnt) {
        max_cnt = c;
        min_val = x;
      } else if (c == max_cnt) {
        min_val = min(min_val, x);
      }
    };

    vector<int> ans(m, -1);
    int block_size = ceil(n / sqrt(m * 2));

    struct Query {
      int bid, l, r, threshold, qid; // [l,r) 左闭右开
    };

    vector<Query> qs;
    for (int i = 0; i < m; i++) {
      auto &q = queries[i];
      int l = q[0], r = q[1] + 1, threshold = q[2]; // 左闭右开

      // 大区间离线（保证 l 和 r 不在同一个块中）
      if (r - l > block_size) {
        qs.emplace_back(l / block_size, l, r, threshold, i);
        continue;
      }

      // 小区间暴力
      for (int j = l; j < r; j++) {
        add(nums[j]);
      }
      if (max_cnt >= threshold) {
        ans[i] = min_val;
      }

      // 重置数据
      cnt.clear();
      max_cnt = 0;
    }

    ranges::sort(qs, {}, [](auto &q) { return pair(q.bid, q.r); });

    int r;
    for (int i = 0; i < qs.size(); i++) {
      auto &q = qs[i];
      int l0 = (q.bid + 1) * block_size;
      if (i == 0 || q.bid > qs[i - 1].bid) {
        // 遍历到一个新的块
        r = l0; // 右端点移动的起点
        // 重置数据
        cnt.clear();
        max_cnt = 0;
      }

      // 右端点从 r 移动到 q.r（q.r 不计入）
      for (; r < q.r; r++) {
        add(nums[r]);
      }

      int tmp_max_cnt = max_cnt, tmp_min_val = min_val;

      // 左端点从 l0 移动到 q.l（l0 不计入）
      for (int j = q.l; j < l0; j++) {
        add(nums[j]);
      }
      if (max_cnt >= q.threshold) {
        ans[q.qid] = min_val;
      }

      // 回滚
      max_cnt = tmp_max_cnt;
      min_val = tmp_min_val;
      for (int j = q.l; j < l0; j++) {
        cnt[nums[j]]--;
      }
    }
    return ans;
  }
};

