#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minMoves(int sx, int sy, int x, int y) {
    int ans = 0;
    for (; x != sx || y != sy; ans++) {
      if (x < sx || y < sy) {
        return -1;
      }
      if (x == y) {
        if (sy > 0) {
          x = 0;
        } else {
          y = 0;
        }
        continue;
      }
      // 保证 x > y
      if (x < y) {
        swap(x, y);
        swap(sx, sy);
      }
      if (x > y * 2) {
        if (x % 2 > 0) {
          return -1;
        }
        x /= 2;
      } else {
        x -= y;
      }
    }
    return ans;
  }
};
