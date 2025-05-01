#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<int> pathExistenceQueries(int n, vector<int> &nums, int maxDiff, vector<vector<int>> &queries) {
    vector<array<int, 2>> vec;
    for (int i = 0; i < n; i++) {
      vec.push_back({nums[i], i});
    }
    ranges::sort(vec);

    const int m = 20;
    int f[n][m];
    for (int i = n - 1, j = n - 1; i >= 0; i--) {
      while (vec[j][0] - vec[i][0] > maxDiff) j--;
      int x = vec[i][1], y = vec[j][1];

      f[x][0] = y;
      for (int p = 1; p < m; p++) f[x][p] = f[f[x][p - 1]][p - 1];
    }

    vector<int> res;
    for (auto &qry: queries) {
      int x = qry[0], y = qry[1];
      if (nums[x] > nums[y]) {
        swap(x, y);
      }
      if (x == y) {
        res.push_back(0);
        continue;
      }

      int d = 0;
      for (int p = m - 1; p >= 0; p--) {
        if (nums[f[x][p]] < nums[y]) {
          d |= 1 << p;
          x = f[x][p];
        }
      }
      if (nums[f[x][0]] < nums[y]) res.push_back(-1);
      else res.push_back(d + 1);
    }
    return res;
  }
};
