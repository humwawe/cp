#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long minCuttingCost(int n, int m, int k) {
    if (n > k) {
      return 1ll * k * (n - k);
    }
    if (m > k) {
      return 1ll * k * (m - k);
    }
    return 0;
  }
};
