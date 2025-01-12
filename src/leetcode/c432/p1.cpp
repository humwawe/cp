#include <lc-util.h>


class Solution {
public:
  vector<int> zigzagTraversal(vector<vector<int> > &grid) {
    int n = grid.size(), m = grid[0].size();
    vector<int> res;
    int i = 0, j = 0;
    while (i < n) {
      res.emplace_back(grid[i][j]);
      if (i % 2 == 0) j += 2;
      else j -= 2;
      if (j >= m) {
        i += 1;
        j = j == m ? m - 1 : m - 2;
      }
      if (j <= -1) {
        i += 1;
        j = j == -1 ? 0 : 1;
      }
    }
    return res;
  }
};
