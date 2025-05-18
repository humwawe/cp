#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int minMoves(vector<string> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    map<char, vector<array<int, 2>>> mp;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if ('A' <= matrix[i][j] && matrix[i][j] <= 'Z') {
          mp[matrix[i][j]].push_back({i, j});
        }
      }
    }
    queue<array<int, 2>> q;
    vector dis(n, vector<int>(m, -1));
    q.push({0, 0});
    dis[0][0] = 0;
    if (mp.contains(matrix[0][0])) {
      for (auto &[x, y]: mp[matrix[0][0]]) {
        q.push({x, y});
        dis[x][y] = 0;
      }
    }
    vector dx = {0, 0, 1, -1};
    vector dy = {1, -1, 0, 0};
    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && matrix[nx][ny] != '#' && dis[nx][ny] == -1 && dis[nx][ny] > dis[x]
            [y] + 1) {
          q.push({nx, ny});
          dis[nx][ny] = dis[x][y] + 1;
          if (mp.contains(matrix[nx][ny])) {
            for (auto &[xx, yy]: mp[matrix[nx][ny]]) {
              q.push({xx, yy});
              dis[xx][yy] = dis[nx][ny];
            }
          }
        }
      }
    }
    return dis[n - 1][m - 1];
  }
};
