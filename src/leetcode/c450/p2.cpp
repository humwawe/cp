#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  int minSwaps(vector<int> &nums) {
    int n = nums.size();
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; ++i) {
      int t = nums[i];
      int cur{};
      while (t) {
        cur += t % 10;
        t /= 10;
      }
      a[i] = {cur, nums[i], i};
    }
    ranges::sort(a);
    vector<bool> vis(n);

    int res{};
    for (int i = 0; i < n; i++) {
      if (!vis[i]) {
        int t = i;
        int cnt{};
        while (!vis[t]) {
          vis[t] = true;
          t = a[t][2];
          cnt++;
        }
        res += cnt - 1;
      }
    }
    return res;
  }
};
