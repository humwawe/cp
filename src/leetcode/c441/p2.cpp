#ifdef LC_LOCAL
#include<lc-util.h>
#endif
class Solution {
public:
  vector<int> solveQueries(vector<int> &nums, vector<int> &queries) {
    int n = nums.size();
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
      nums.push_back(nums[i]);
      cnt[nums[i]]++;
    }
    vector vis(n, 2 * n + 2);
    for (int q: queries) {
      vis[q] = 2 * n + 1;
    }
    map<int, int> mp;
    for (int i = 0; i < 2 * n; i++) {
      if (vis[i % n] <= 2 * n + 1) {
        if (mp.contains(nums[i])) {
          vis[i % n] = min(vis[i % n], i - mp[nums[i]]);
        }
      }
      mp[nums[i]] = i;
    }
    mp.clear();

    for (int i = 2 * n - 1; i >= 0; i--) {
      if (vis[i % n] <= 2 * n + 1) {
        if (mp.contains(nums[i])) {
          vis[i % n] = min(vis[i % n], mp[nums[i]] - i);
        }
      }
      mp[nums[i]] = i;
    }
    vector<int> res;
    for (int i: queries) {
      if (cnt[nums[i]] == 1) {
        res.push_back(-1);
      } else if (vis[i] < n + 1) {
        res.push_back(vis[i]);
      }
    }
    return res;
  }
};
