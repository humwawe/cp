#include <lc-util.h>

class Solution {
public:
  int maxDistance(int side, vector<vector<int>> &points, int k) {
    vector<long long> a;
    for (auto &p: points) {
      int x = p[0], y = p[1];
      if (x == 0) {
        a.push_back(y);
      } else if (y == side) {
        a.push_back(side + x);
      } else if (x == side) {
        a.push_back(side * 3LL - y);
      } else {
        a.push_back(side * 4LL - x);
      }
    }
    ranges::sort(a);

    auto check = [&](int mid) -> bool {
      for (long long start: a) {
        long long end = start + side * 4LL - mid;
        long long cur = start;
        for (int i = 0; i < k - 1; i++) {
          auto it = ranges::lower_bound(a, cur + mid);
          if (it == a.end() || *it > end) {
            cur = -1;
            break;
          }
          cur = *it;
        }
        if (cur >= 0) {
          return true;
        }
      }
      return false;
    };


    int l = 0, r = side;
    while (l < r) {
      int mid = l + r + 1 >> 1;
      if (check(mid)) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    return l == 0 ? -1 : l;
  }
};
