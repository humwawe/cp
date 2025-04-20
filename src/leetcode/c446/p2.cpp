#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int maximumPossibleSize(vector<int> &nums) {
    int n = nums.size();
    int last = nums[0];
    int res{1};
    for (int i = 1; i < n; i++) {
      if (nums[i] >= last) {
        res++;
        last = nums[i];
      }
    }
    return res;
  }
};
