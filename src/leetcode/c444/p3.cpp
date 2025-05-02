#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int maxProduct(vector<int> &nums, int k, int limit) {
    int total = reduce(nums.begin(), nums.end());
    if (total < abs(k)) {
      return -1;
    }
    int n = nums.size(), ans = -1;
    unordered_set<long long> vis;
    auto dfs = [&](this auto &&dfs, int i, int s, int m, bool odd, bool empty) -> void {
      if (ans == limit || m > limit && ans >= 0) {
        // 无法让 ans 变得更大
        return;
      }

      if (i == n) {
        if (!empty && s == k && m <= limit) {
          // 合法子序列
          ans = max(ans, m); // 用合法子序列的元素积更新答案的最大值
        }
        return;
      }

      long long mask = (long long) i << 32 | (s + total) << 15 | m << 2 | odd << 1 | empty;
      if (!vis.insert(mask).second) {
        // mask 在 vis 中
        return;
      }

      // 不选 x
      dfs(i + 1, s, m, odd, empty);
      // 选 x
      int x = nums[i];
      dfs(i + 1, s + (odd ? -x : x), min(m * x, limit + 1), !odd, false);
    };
    dfs(0, 0, 1, false, true);
    return ans;
  }
};
