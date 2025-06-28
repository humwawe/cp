#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  bool canMakeEqual(vector<int> &nums, int k) {
    int n = nums.size();
    auto check = [&](int v) -> bool {
      vector<int> a = nums;
      int cnt{};
      for (int i = 0; i < n - 1; i++) {
        if (a[i] != v) {
          a[i + 1] = -a[i + 1];
          cnt++;
        }
      }
      return a[n - 1] == v && cnt <= k;
    };
    if (check(1) || check(-1)) {
      return true;
    }
    return false;
  }
};
