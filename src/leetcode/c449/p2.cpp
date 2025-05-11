#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  bool canPartitionGrid(vector<vector<int>> &grid) {
    int n = grid.size(), m = grid[0].size();
    long long sum{};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        sum += grid[i][j];
      }
    }
    long long t{};
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < m; j++) {
        t += grid[i][j];
      }
      if (t * 2 == sum) {
        return true;
      }
    }

    t = 0;
    for (int j = 0; j < m - 1; j++) {
      for (int i = 0; i < n; i++) {
        t += grid[i][j];
      }
      if (t * 2 == sum) {
        return true;
      }
    }
    return false;
  }
};
