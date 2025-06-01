#ifdef LC_LOCAL
#include<lc-util.h>
#endif
using i64 = long long;


class Solution {
public:
  int minMoves(vector<string> &classroom, int energy) {
    int n = classroom.size(), m = classroom[0].size();
    array start{0, 0};
    map<array<int, 2>, int> mp;
    int idx{};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (classroom[i][j] == 'S') {
          start = {i, j};
        }
        if (classroom[i][j] == 'L') {
          mp[{i, j}] = idx++;
        }
      }
    }
    int lim = (1 << idx);

    int inf = 1e9;
    vector<array<int, 2>> dirs{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    // vector vis(n, vector(m, vector(energy + 1, vector(lim, false))));
    vector dist(n, vector(m, vector(energy + 1, vector(lim, inf))));
    queue<tuple<int, int, int, int>> q;
    q.emplace(start[0], start[1], energy, 0);
    dist[start[0]][start[1]][energy][0] = 0;
    while (!q.empty()) {
      auto [x,y,e,st] = q.front();
      q.pop();

      if (st == lim - 1) {
        return dist[x][y][e][st];
      }
      if (e == 0) {
        continue;
      }

      for (auto [dx, dy]: dirs) {
        int nx = x + dx, ny = y + dy;
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
          continue;
        }
        if (classroom[nx][ny] == 'X') {
          continue;
        }
        int ne = e - 1;
        if (classroom[nx][ny] == 'R') {
          ne = energy;
        }
        int nst = st;
        if (mp.contains({nx, ny})) {
          nst |= (1 << mp[{nx, ny}]);
        }
        if (dist[nx][ny][ne][nst] == inf) {
          dist[nx][ny][ne][nst] = dist[x][y][e][st] + 1;
          q.emplace(nx, ny, ne, nst);
        }
      }
    }

    return -1;
  }
};
