#include <lc-util.h>

class Solution {
public:
  int countArrays(vector<int> &original, vector<vector<int>> &bounds) {
    int n = original.size();
    int l = -2e9, r = 2e9;
    for (int i = 0; i < n; i++) {
      l = max(l, bounds[i][0] - original[i]);
      r = min(r, bounds[i][1] - original[i]);
    }
    return max(0, r - l + 1);
  }
};
