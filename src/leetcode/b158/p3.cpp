#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  long long maxGCDScore(vector<int> &nums, int k) {
    int n = nums.size();
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
      int tmp = nums[i];
      while (tmp % 2 == 0) {
        t[i]++;
        tmp /= 2;
      }
    }
    long long res{};
    for (int i = 0; i < n; i++) {
      int g{}, mn = 1e9, cnt{};
      for (int j = i; j < n; j++) {
        g = gcd(g, nums[j]);
        if (t[j] < mn) {
          mn = t[j];
          cnt = 1;
        } else if (t[j] == mn) {
          cnt++;
        }
        long long tmp = 1ll * g * (j - i + 1);
        if (cnt <= k) {
          tmp *= 2;
        }
        res = max(res, tmp);
      }
    }
    return res;
  }
};
