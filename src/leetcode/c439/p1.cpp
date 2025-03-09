#include <lc-util.h>

class Solution {
public:
  int largestInteger(vector<int> &nums, int k) {
    int n = nums.size();
    unordered_map<int, int> cnt;

    for (int i = 0; i + k <= n; i++) {
      unordered_set<int> st;
      for (int j = 0; j < k; j++)
        st.insert(nums[i + j]);
      for (int x: st) cnt[x]++;
    }
    int res = -1;
    for (auto &p: cnt)
      if (p.second == 1)
        res = max(res, p.first);
    return res;
  }
};
