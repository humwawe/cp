#ifdef LC_LOCAL
#include<lc-util.h>
#endif

vector<int> Z(string s) {
  int n = s.size();
  vector<int> z(n);
  z[0] = n;
  for (int i = 1, j = 1; i < n; i++) {
    z[i] = max(0, min(j + z[j] - i, z[i - j]));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] > j + z[j]) {
      j = i;
    }
  }
  return z;
}


class Solution {
public:
  int countCells(vector<vector<char>> &grid, string pattern) {
    int n = grid.size(), m = grid[0].size();
    string r{}, c{};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        r += grid[i][j];
      }
    }
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        c += grid[j][i];
      }
    }
    vector<int> z1 = Z(pattern + "#" + r);

    int s = pattern.size() + 1;
    vector<int> diff1(n * m + 1);
    for (int i = s; i < s + r.size(); i++) {
      if (z1[i] == pattern.size()) {
        diff1[i - s]++;
        diff1[i - 1]--;
      }
    }


    for (int i = 1; i <= n * m; i++) {
      diff1[i] += diff1[i - 1];
    }
    vector<int> diff2(n * m + 1);
    vector<int> z2 = Z(pattern + "#" + c);
    for (int i = s; i < s + c.size(); i++) {
      if (z2[i] == pattern.size()) {
        diff2[i - s]++;
        diff2[i - 1]--;
      }
    }
    for (int i = 1; i <= n * m; i++) {
      diff2[i] += diff2[i - 1];
    }
    int res{};
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (diff1[i * m + j] > 0 && diff2[i + j * n] > 0) {
          res++;
        }
      }
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  Solution solution;
  vector<vector<char>> g{{{'a'}}};
  cout << solution.countCells(g, "a") << endl;
}
