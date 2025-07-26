#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int countIslands(vector<vector<int>> &grid, int k) {
    int m = grid.size(), n = grid[0].size();
    vector<array<int, 2>> DIRS = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    function<long long(int, int)> dfs = [&](int i, int j) -> long long {
      long long res = grid[i][j];
      grid[i][j] = 0; // 标记为访问过
      for (auto [dx, dy]: DIRS) {
        int x = i + dx, y = j + dy;
        if (0 <= x && x < m && 0 <= y && y < n && grid[x][y]) {
          res += dfs(x, y);
        }
      }
      return res;
    };

    int ans = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] && dfs(i, j) % k == 0) {
          ans++;
        }
      }
    }
    return ans;
  }
};
