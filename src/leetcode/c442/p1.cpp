#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  int maxContainers(int n, int w, int maxWeight) {
    return min(maxWeight / w, n * n);
  }
};
