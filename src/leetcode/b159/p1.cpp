#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int minSwaps(vector<int> &nums) {
    int n = nums.size();
    int cnt1{}, cnt2{};
    vector<int> p1, p2;
    for (int i = 0; i < n; i++) {
      if (nums[i] % 2 == 0) {
        cnt1++;
        p1.push_back(i);
      } else {
        cnt2++;
        p2.push_back(i);
      }
    }
    if (abs(cnt1 - cnt2) > 1) {
      return -1;
    }
    int res{};
    if (cnt1 > cnt2) {
      for (int i = 0, j = 0; i < n; i += 2, j++) {
        res += abs(p1[j] - i);
      }
    } else if (cnt2 > cnt1) {
      for (int i = 0, j = 0; i < n; i += 2, j++) {
        res += abs(p2[j] - i);
      }
    } else {
      int t1{}, t2{};
      for (int i = 0, j = 0; i < n; i += 2, j++) {
        t1 += abs(p1[j] - i);
        t2 += abs(p2[j] - i);
      }
      res = min(t1, t2);
    }
    return res;
  }
};
