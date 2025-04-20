#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int uniqueXorTriplets(vector<int> &nums) {
    int n = nums.size();
    if (n <= 2) {
      return n;
    }
    return 1 << bit_width((size_t) n);
  }
};
