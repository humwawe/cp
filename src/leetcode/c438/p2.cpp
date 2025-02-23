#include <lc-util.h>

class Solution {
public:
  long long maxSum(vector<vector<int>> &grid, vector<int> &limits, int k) {
    if (k == 0) {
      return 0;
    }
    int n = grid.size(), m = grid[0].size();
    vector<array<int, 2>> a;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        a.push_back({grid[i][j], i});
      }
    }
    long long res{};
    ranges::sort(a, greater());
    for (int i = 0; i < n * m; i++) {
      if (limits[a[i][1]]) {
        limits[a[i][1]]--;
        res += a[i][0];
        if (--k == 0) {
          break;
        }
      }
    }
    return res;
  }
};
