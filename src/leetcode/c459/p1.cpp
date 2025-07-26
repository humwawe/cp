#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  bool checkDivisibility(int n) {
    int x{}, y{1};
    for (int t = n; t; t /= 10) {
      x += t % 10;
      y *= t % 10;
    }
    return n % (x + y) == 0;
  }
};
