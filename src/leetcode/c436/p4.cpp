#include <lc-util.h>

class Solution {
public:
  long long maxScore(vector<int> &points, int m) {
    int n = points.size();
    long long l{}, r{1ll * m * ranges::max(points)};
    points.push_back(0);
    auto check = [&](long long mid) {
      long long cnt{};
      vector<long long> g(n + 1);
      int last{-1};
      for (int i = 0; i < n; i++) {
        if (g[i] < mid) {
          cnt += i - last;
          g[i] += points[i];
          last = i;
          if (g[i] < mid) {
            long long c = (mid - g[i] + points[i] - 1) / points[i];
            g[i + 1] += c * points[i + 1];
            cnt += c * 2;
            last = i;
          }
          if (cnt > m) {
            return false;
          }
        }
      }
      return cnt <= m;
    };

    while (l < r) {
      long long mid = l + r + 1 >> 1;
      if (check(mid)) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    return l;
  }
};
