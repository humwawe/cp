#include <lc-util.h>

class Solution {
public:
  double separateSquares(vector<vector<int>> &squares) {
    vector<int> a;
    double l{0}, r{2e9};
    double all{0};
    for (auto &square: squares) {
      all += (double) square[2] * square[2];
    }

    while (r - l > 1e-6) {
      double m = (l + r) / 2;
      double tmp{0};
      for (auto &square: squares) {
        if (square[1] >= m) {
          continue;
        }
        tmp += square[2] * (min((double) square[1] + square[2], m) - square[1]);
      }
      if (tmp - (all - tmp) < 0) {
        l = m;
      } else {
        r = m;
      }
    }
    return l;
  }
};
