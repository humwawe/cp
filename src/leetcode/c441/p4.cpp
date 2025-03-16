#ifdef LC_LOCAL
#include<lc-util.h>
#endif

long long solve(int x) {
  vector<int> nums;
  while (x > 0) {
    nums.push_back(x % 10);
    x /= 10;
  }
  ranges::reverse(nums);
  map<array<int, 3>, long long> memo;

  function<long long(int, int, int, bool, bool)> dfs = [&](int i, int p, int s, bool limit, bool lead) {
    // 算到nums的最后一位
    if (i == nums.size()) {
      return lead ? 0 : (p % s == 0 ? 1ll : 0);
    }
    if (!limit && !lead && memo.contains({i, p, s})) {
      return memo[{i, p, s}];
    }

    long long res = 0;
    // 可以跳过当前数位
    if (lead) {
      res = dfs(i + 1, p, s, false, true);
    }

    int up = limit ? nums[i] : 9;
    // 根据前导0判断是否能取到0
    int low = lead ? 1 : 0;

    for (int j = low; j <= up; j++) {
      // 处理某种条件
      res += dfs(i + 1, p * j, s + j, limit && j == up, false);
    }
    if (!limit && !lead) {
      memo[{i, p, s}] = res;
    }
    return res;
  };
  return dfs(0, 1, 0, true, true);
}


class Solution {
public:
  int beautifulNumbers(int l, int r) {
    return solve(r) - solve(l - 1);
  }
};
