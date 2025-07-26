#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int findMaxPathScore(vector<vector<int>> &edges, vector<bool> &online, long long K) {
    int n = online.size();
    vector<vector<int>> e(n), v(n);
    for (auto &edge: edges) {
      e[edge[1]].push_back(edge[0]);
      v[edge[1]].push_back(edge[2]);
    }

    vector<long long> f(n);
    // 求从节点 0 到 sn，且经过的边权都大于等于 LIM 的最短路
    auto dp = [&](this auto &&dp, int sn, int LIM) -> long long {
      if (sn == 0) return 0;
      long long &ret = f[sn];
      if (ret >= 0) return ret;
      ret = K + 1;

      for (int i = 0; i < e[sn].size(); i++) {
        int fn = e[sn][i];
        if (!online[fn] || v[sn][i] < LIM) continue;
        ret = min(ret, dp(fn, LIM) + v[sn][i]);
      }
      return ret;
    };

    auto check = [&](int LIM) {
      for (int i = 0; i < n; i++) f[i] = -1;
      return dp(n - 1, LIM) <= K;
    };

    // 连答案 0 都不可行，则无解
    if (!check(0)) return -1;
    // 二分答案
    int head = 0, tail = 1e9;
    while (head < tail) {
      int mid = (head + tail + 1) >> 1;
      if (check(mid)) head = mid;
      else tail = mid - 1;
    }
    return head;
  }
};
