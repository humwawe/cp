#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
  string trans(int v, int base) {
    string s;
    while (v > 0) {
      int d = v % base;
      s += d < 10 ? '0' + d : 'A' + d - 10;
      v /= base;
    }
    ranges::reverse(s);
    return s;
  }

public:
  string concatHex36(int n) {
    return trans(n * n, 16) + trans(n * n * n, 36);
  }
};
