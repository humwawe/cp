#include<lc-util.h>

class Solution {
public:
  int maxFreeTime(int eventTime, vector<int> &startTime, vector<int> &endTime) {
    int n = startTime.size();
    vector<int> a;
    a.push_back(startTime[0]);
    for (int i = 0; i < n - 1; i++) {
      a.push_back(startTime[i + 1] - endTime[i]);
    }
    a.push_back(eventTime - endTime[n - 1]);
    n += 1;
    vector<int> pre(n), suf(n);
    pre[0] = a[0];
    for (int i = 1; i < n; i++) {
      pre[i] = max(pre[i - 1], a[i]);
    }
    suf[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--) {
      suf[i] = max(suf[i + 1], a[i]);
    }
    int res = 0;
    for (int i = 0; i < n - 1; i++) {
      int cur = endTime[i] - startTime[i];
      if ((i - 1 >= 0 && pre[i - 1] >= cur) || (i + 2 < n && suf[i + 2] >= cur)) {
        res = max(res, a[i] + a[i + 1] + cur);
      } else {
        res = max(res, a[i] + a[i + 1]);
      }
    }
    return res;
  }
};
