#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long maximumProduct(vector<int> &nums, int m) {
    int n = nums.size();
    int mi = nums[0], mx = nums[0];
    long long res = LONG_MIN;
    for (int i = m - 1; i < n; i++) {
      mi = min(mi, nums[i - m + 1]);
      mx = max(mx, nums[i - m + 1]);
      res = ranges::max({res, 1ll * mi * nums[i], 1ll * mx * nums[i]});
    }
    return res;
  }
};
