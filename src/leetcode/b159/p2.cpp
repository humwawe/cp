#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long maxArea(vector<vector<int>> &coords) {
    int n = coords.size();
    function<long long()> solve = [&]() -> long long {
      map<int, vector<int>> mp;
      for (int i = 0; i < n; i++) {
        mp[coords[i][0]].push_back(coords[i][1]);
      }
      int m1 = mp.begin()->first;
      int m2 = mp.rbegin()->first;

      long long res{-1};
      for (auto &[x, ys]: mp) {
        ranges::sort(ys);
        if (ys.size() >= 2) {
          if (x != m1) {
            res = max(res, 1LL * (ys.back() - ys.front()) * (x - m1));
          }
          if (x != m2) {
            res = max(res, 1LL * (ys.back() - ys.front()) * (m2 - x));
          }
        }
      }
      return res;
    };

    long long res1 = solve();
    for (auto &v: coords) {
      swap(v[0], v[1]);
    }
    return max(res1, solve());
  }
};
