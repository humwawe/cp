#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int uniqueXorTriplets(vector<int> &nums) {
    int m = ranges::max(nums) * 2;
    vector<int> f(m);
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        f[nums[i] ^ nums[j]] = 1;
      }
    }
    vector<int> g(m);
    for (int i = 0; i < m; i++) {
      if (f[i]) {
        for (int x: nums) {
          g[i ^ x] = 1;
        }
      }
    }
    return ranges::count(g, 1);
  }
};
