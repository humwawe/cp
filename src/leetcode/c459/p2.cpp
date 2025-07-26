#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int countTrapezoids(vector<vector<int>> &points) {
    unordered_map<int, int> cnt;
    for (auto &p: points) cnt[p[1]]++;

    const int MOD = 1e9 + 7;
    long long ans{}, sm{};
    for (auto &p: cnt) {
      long long t = 1LL * p.second * (p.second - 1) / 2 % MOD;
      ans = (ans + sm * t) % MOD;
      sm = (sm + t) % MOD;
    }
    return ans;
  }
};
