#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<int> findCoins(vector<int> &numWays) {
    int n = numWays.size();
    vector<int> f(n + 1);
    f[0] = 1;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      int ways = numWays[i - 1];
      if (ways == f[i]) {
        continue;
      }
      if (ways - 1 != f[i]) {
        return {};
      }
      ans.push_back(i);
      for (int j = i; j <= n; j++) {
        f[j] += f[j - i];
      }
    }
    return ans;
  }
};
