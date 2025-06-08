#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxSumDistinctTriplet(vector<int> &x, vector<int> &y) {
    int n = x.size();
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
      mp[x[i]].push_back(y[i]);
    }
    vector<int> t;
    for (auto &[k, v]: mp) {
      t.push_back(ranges::max(v));
    }
    ranges::sort(t, greater{});
    if (t.size() <= 2) {
      return -1;
    }
    int res{};
    for (int i = 0; i < 3; i++) {
      res += t[i];
    }
    return res;
  }
};
