#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  long long maximumMedianSum(vector<int> &nums) {
    long long res{};
    int n = nums.size();
    n /= 3;
    ranges::sort(nums, greater());
    int j{1};
    for (int i = 0; i < n; i++) {
      res += nums[j];
      j += 2;
    }
    return res;
  }
};
