#include <lc-util.h>
using i64 = long long;

class Solution {
public:
  long long countNonDecreasingSubarrays(vector<int> &nums, int k) {
    int n = nums.size();
    vector<i64> sum(n);
    sum[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      sum[i] = sum[i - 1] + nums[i];
    }
    vector right(n, n);
    vector<vector<int>> vec(n);
    stack<int> stk;
    for (int i = 0; i < n; i++) {
      while (!stk.empty() && nums[stk.top()] <= nums[i]) {
        right[stk.top()] = i;
        stk.pop();
      }
      if (!stk.empty()) {
        vec[stk.top()].emplace_back(i);
      }
      stk.push(i);
    }
    auto calc = [&](int i, int lim) {
      lim = min(lim, right[i] - 1);
      return 1LL * nums[i] * (lim - i) - (sum[lim] - sum[i]);
    };

    i64 res = 0, now = 0;
    deque<int> dq;
    for (int i = 0, j = 0; i < n; i++) {
      while (!dq.empty() && nums[dq.back()] <= nums[i]) {
        dq.pop_back();
      }
      dq.push_back(i);
      now += nums[dq.front()] - nums[i];

      while (j < i && now > k) {
        now -= calc(j, i);
        for (int &x: vec[j]) {
          if (x > i) break;
          now += calc(x, i);
        }
        if (dq.front() == j) dq.pop_front();
        j++;
      }
      res += i - j + 1;
    }
    return res;
  }
};
