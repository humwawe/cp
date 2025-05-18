#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  int smallestIndex(vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) {
      int t = nums[i];
      int cur{};
      while (t) {
        cur += t % 10;
        t /= 10;
      }
      if (cur == i) {
        return i;
      }
    }
    return -1;
  }
};
