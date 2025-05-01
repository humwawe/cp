#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  vector<int> concatenatedDivisibility(vector<int> &nums, int k) {
    int n = nums.size();
    ranges::sort(nums);
    vector<int> len(n);
    for (int i = 0; i < n; i++) {
      int t = 1, x = nums[i];
      while (x) { t *= 10, x /= 10; }
      len[i] = t;
    }

    vector memo(1 << n, vector<int>(k, -1));
    vector<int> res;
    function<bool(int, int)> dfs = [&](int st, int m)-> bool {
      if (st == (1 << n) - 1) {
        return m == 0;
      }
      if (memo[st][m] != -1) {
        return memo[st][m];
      }
      for (int i = 0; i < n; i++) {
        if (st >> i & 1) {
          continue;
        }
        res.push_back(nums[i]);
        if (dfs(st | (1 << i), (m * len[i] + nums[i]) % k)) {
          memo[st][m] = true;
          return true;
        }
        res.pop_back();
      }
      memo[st][m] = false;
      return false;
    };
    dfs(0, 0);
    return res;
  }
};
