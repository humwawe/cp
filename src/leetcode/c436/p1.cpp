#include <lc-util.h>

class Solution {
public:
  vector<vector<int>> sortMatrix(vector<vector<int>> &grid) {
    int n = grid.size();
    vector res(n, vector<int>(n));
    for (int i = n - 1, j{}; i >= 0; i--) {
      vector<array<int, 2>> a;
      vector<int> b;
      for (int x = i, y = j; x < n && y < n; x++, y++) {
        a.push_back({x, y});
        b.push_back(grid[x][y]);
      }
      ranges::sort(b, greater());
      for (int k = 0; k < a.size(); k++) {
        res[a[k][0]][a[k][1]] = b[k];
      }
    }

    for (int j = 1, i{}; j < n; j++) {
      vector<array<int, 2>> a;
      vector<int> b;
      for (int x = i, y = j; x < n && y < n; x++, y++) {
        a.push_back({x, y});
        b.push_back(grid[x][y]);
      }
      ranges::sort(b);
      for (int k = 0; k < a.size(); k++) {
        res[a[k][0]][a[k][1]] = b[k];
      }
    }
    return res;
  }
};
