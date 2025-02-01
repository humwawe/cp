#include <lc-util.h>

class Solution {
public:
  int maxFreeTime(int eventTime, int k, vector<int> &startTime, vector<int> &endTime) {
    int n = startTime.size();
    vector<int> a;
    a.push_back(startTime[0]);
    for (int i = 0; i < n - 1; i++) {
      a.push_back(startTime[i + 1] - endTime[i]);
    }
    a.push_back(eventTime - endTime[n - 1]);
    int res = 0;
    k += 1;
    for (int i = 0; i < min(k, n + 1); i++) {
      res += a[i];
    }
    int t = res;
    for (int i = k; i < n + 1; i++) {
      t += a[i];
      t -= a[i - k];
      res = max(res, t);
    }
    return res;
  }
};
