#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size();
    int m = queries.size();
    vector<int> used;
    for (int i = 0; i < n; i++) {
      if (nums[i] == 0) {
        used.push_back(0);
        continue;
      }
      vector<int> dp(nums[i] + 1);
      dp[nums[i]] = 1;
      for (int j = 0; j < m; j++) {
        if (queries[j][0] <= i && i <= queries[j][1]) {
          vector<int> ndp(nums[i] + 1);
          for (int v = 0; v <= nums[i]; v++) {
            if (dp[v]) {
              ndp[v] = 1;
              if (v - queries[j][2] >= 0) {
                ndp[v - queries[j][2]] = 1;
              }
            }
          }
          dp = ndp;
          if (dp[0]) {
            used.push_back(j + 1);
            break;
          }
        }
      }
      if (used.size() != i + 1) {
        return -1;
      }
    }
    return ranges::max(used);
  }
};
