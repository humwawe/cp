#include <lc-util.h>


class Solution {
public:
  int maxAdjacentDistance(vector<int> &nums) {
    nums.emplace_back(nums[0]);
    int n = nums.size();
    int res = 0;
    for (int i = 0; i < n - 1; i++) {
      res = max(res, abs(nums[i] - nums[i + 1]));
    }
    return res;
  }
};
