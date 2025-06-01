#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  bool checkEqualPartitions(vector<int> &nums, long long target) {
    int n = nums.size();
    bool res{};
    function<void(int, long long, long long)> dfs = [&](int i, long long x, long long y) {
      if (x > target || y > target) {
        return;
      }
      if (i == n) {
        if (x == target && y == target) {
          res = true;
        }
        return;
      }
      if (x == -1) {
        dfs(i + 1, nums[i], y);
      } else {
        dfs(i + 1, x * nums[i], y);
      }

      if (y == -1) {
        dfs(i + 1, x, nums[i]);
      } else {
        dfs(i + 1, x, y * nums[i]);
      }
    };

    dfs(0, -1, -1);
    return res;
  }
};
