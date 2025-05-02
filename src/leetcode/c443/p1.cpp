#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  vector<int> minCosts(vector<int> &cost) {
    int n = cost.size();
    vector<int> res(n);
    res[0] = cost[0];
    for (int i = 1; i < n; ++i) {
      res[i] = min(cost[i], res[i - 1]);
    }
    return res;
  }
};
