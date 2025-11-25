#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minRemoval(vector<int> &nums, int k) {
    int n = nums.size();
    ranges::sort(nums);
    long long cur = 1ll * nums[0] * k;
    int idx = ranges::lower_bound(nums, cur + 1) - nums.begin();
    int res = n - idx;
    for (int i = 0; i < n - 1; i++) {
      long long cur = 1ll * nums[i + 1] * k;
      idx = ranges::lower_bound(nums, cur + 1) - nums.begin();
      res = min(res, n - idx + i + 1);
    }
    return res;
  }
};
