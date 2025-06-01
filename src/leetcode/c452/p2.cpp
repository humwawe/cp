#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<vector<int>> minAbsDiff(vector<vector<int>> &grid, int k) {
    int n = grid.size(), m = grid[0].size();
    int inf = INT_MAX;
    vector res(n - k + 1, vector(m - k + 1, inf));
    for (int i = 0; i + k - 1 < n; i++) {
      for (int j = 0; j + k - 1 < m; j++) {
        set<int> st;
        for (int x = 0; x < k; x++) {
          for (int y = 0; y < k; y++) {
            st.insert(grid[i + x][j + y]);
          }
        }
        if (st.size() == 1) {
          res[i][j] = 0;
        } else {
          int last = inf;
          for (const auto &x: st) {
            if (last != inf) {
              res[i][j] = min(res[i][j], abs(last - x));
            }
            last = x;
          }
        }
      }
    }
    return res;
  }
};
