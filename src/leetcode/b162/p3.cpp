#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration, vector<int> &waterStartTime,
                         vector<int> &waterDuration) {
    function<int()> solve = [&]() {
      int n = landStartTime.size();
      int m = waterStartTime.size();
      int fin = 1e9;
      for (int i = 0; i < n; i++) {
        fin = min(fin, landStartTime[i] + landDuration[i]);
      }
      int res = 1e9;
      for (int i = 0; i < m; i++) {
        res = min(res, max(fin, waterStartTime[i]) + waterDuration[i]);
      }
      return res;
    };
    int res = solve();
    swap(landStartTime, waterStartTime);
    swap(landDuration, waterDuration);
    return min(res, solve());
  }
};
