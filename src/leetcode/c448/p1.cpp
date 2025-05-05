#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int maxProduct(int n) {
    vector<int> a;
    while (n) {
      a.push_back(n % 10);
      n /= 10;
    }
    ranges::sort(a, ranges::greater{});
    return a[0] * a[1];
  }
};
