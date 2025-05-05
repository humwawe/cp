#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  vector<vector<int>> specialGrid(int N) {
    int n = 1 << N;
    vector res(n, vector(n, 0));
    if (N == 0) {
      return res;
    }

    function<void(int, int, int, int)> dfs = [&](int x, int y, int n, int s) {
      if (n == 1) {
        res[x][y] = s + 3;
        res[x][y + 1] = s;
        res[x + 1][y] = s + 2;
        res[x + 1][y + 1] = s + 1;
        return;
      }

      dfs(x, y, n / 2, s + n * n * 3);
      dfs(x, y + n, n / 2, s);
      dfs(x + n, y, n / 2, s + n * n * 2);
      dfs(x + n, y + n, n / 2, s + n * n);
    };
    dfs(0, 0, n / 2, 0);
    return res;
  }
};
