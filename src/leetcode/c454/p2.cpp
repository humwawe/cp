#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int specialTriplets(vector<int> &nums) {
    map<int, int> pre, suf;
    int n = nums.size();
    for (int i = 1; i < n; i++) {
      suf[nums[i]]++;
    }
    long long res{};
    int mod = 1e9 + 7;
    for (int i = 1; i < n - 1; i++) {
      suf[nums[i]]--;
      pre[nums[i - 1]]++;
      res = (res + 1ll * pre[nums[i] * 2] * suf[nums[i] * 2]) % mod;
    }
    return res;
  }
};
