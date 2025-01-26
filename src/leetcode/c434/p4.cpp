#include <lc-util.h>

class Solution {
public:
  vector<vector<int>> supersequences(vector<string> &words) {
    vector<int> sigma;
    for (auto &word: words) for (char c: word) sigma.push_back(c - 'a');
    ranges::sort(sigma);
    sigma.resize(ranges::unique(sigma).begin() - sigma.begin());

    int n = sigma.size();
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++) mp[sigma[i]] = i;
    vector<int> e[n];
    for (auto &word: words) e[mp[word[0] - 'a']].push_back(mp[word[1] - 'a']);

    auto calcLen = [&](const int msk) {
      return __builtin_popcount(msk) + n;
    };

    // msk 为 1 的位表示这种字母出现两次，
    // 对所有只出现一次的字母，检查是否有合法的拓扑排序。
    auto check = [&](int msk) {
      int deg[n];
      memset(deg, 0, sizeof(deg));
      for (int sn = 0; sn < n; sn++)
        if (msk >> sn & 1 ^ 1)
          for (int fn: e[sn]) if (msk >> fn & 1 ^ 1) deg[fn]++;

      int head = 0, tail = 0, q[n];
      for (int i = 0; i < n; i++) if (deg[i] == 0 && (msk >> i & 1 ^ 1)) q[tail++] = i;
      int cnt = 0;
      while (head < tail) {
        int sn = q[head++];
        cnt++;
        for (int fn: e[sn]) if (msk >> fn & 1 ^ 1) if ((--deg[fn]) == 0) q[tail++] = fn;
      }
      return cnt == n - __builtin_popcount(msk);
    };

    int len = 1e9;
    vector<int> ans;
    // 枚举哪些字母出现两次
    for (int i = 0; i < (1 << n); i++)
      if (check(i)) {
        int t = calcLen(i);
        if (t < len) ans.clear(), len = t;
        if (t == len) ans.push_back(i);
      }

    vector<vector<int>> ret;
    for (int msk: ans) {
      vector<int> tmp(26);
      for (int j = 0; j < n; j++) {
        if (msk >> j & 1) tmp[sigma[j]] = 2;
        else tmp[sigma[j]] = 1;
      }
      ret.push_back(tmp);
    }
    return ret;
  }
};
