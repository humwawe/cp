#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int maxSum(vector<int> &nums) {
    set<int> st;
    for (auto &i: nums) {
      st.insert(i);
    }
    int res{};
    for (auto &i: st) {
      if (i > 0) {
        res += i;
      }
    }
    if (res == 0 && !st.contains(0)) {
      return *st.rbegin();
    }
    return res;
  }
};
