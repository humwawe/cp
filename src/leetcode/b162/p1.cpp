#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int earliestFinishTime(vector<int> &landStartTime, vector<int> &landDuration, vector<int> &waterStartTime,
                         vector<int> &waterDuration) {
    int n = landStartTime.size();
    int m = waterStartTime.size();
    int res = 1e9;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int t = landStartTime[i] + landDuration[i];
        if (t >= waterStartTime[j]) {
          t = t + waterDuration[j];
        } else {
          t = waterStartTime[j] + waterDuration[j];
        }
        res = min(res, t);

        t = waterStartTime[j] + waterDuration[j];
        if (t >= landStartTime[i]) {
          t += landDuration[i];
        } else {
          t = landStartTime[i] + landDuration[i];
        }
        res = min(res, t);
      }
    }
    return res;
  }
};
