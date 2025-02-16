#include <lc-util.h>

// 字符串哈希模板开始

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(long long x, long long y) {
  return uniform_int_distribution<int>(x, y)(rng);
}

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
  vector<__int128> P, H;

  HashSeq(string s) {
    int n = s.size();
    P.resize(n + 1);
    P[0] = 1;
    for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
    H.resize(n + 1);
    H[0] = 0;
    for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
  }

  long long query(int l, int r) {
    return (H[r] - H[l] * P[r - l] % MOD + MOD) % MOD;
  }
};

// 字符串哈希模板结束

class Solution {
public:
  int shortestMatchingSubstring(string s, string p) {
    int n = s.size(), m = p.size();

    vector<int> star;
    for (int i = 0; i < m; i++) if (p[i] == '*') star.push_back(i);

    HashSeq hs(s);
    // 求 w 在 s 中出现的所有开头下标
    auto gao = [&](string w) {
      int len = w.size();
      HashSeq tmp(w);
      long long goal = tmp.query(1, len);
      vector<int> pos;
      for (int i = 0; i + len <= n; i++) if (len == 0 || hs.query(i, i + len) == goal) pos.push_back(i);
      return pos;
    };
    // 预处理三个子串所有可能的开头下标
    int len1 = star[0];
    auto pos1 = gao(p.substr(0, len1));
    int len2 = star[1] - star[0] - 1;
    auto pos2 = gao(p.substr(star[0] + 1, len2));
    int len3 = m - star[1] - 1;
    auto pos3 = gao(p.substr(star[1] + 1, len3));

    const int INF = 1e9;
    int ans = INF;

    for (int i = 0, j = 0, k = 0; i < pos1.size(); i++) {
      while (j < pos2.size() && pos2[j] < pos1[i] + len1) j++;
      if (j == pos2.size()) break;
      while (k < pos3.size() && pos3[k] < pos2[j] + len2) k++;
      if (k == pos3.size()) break;
      ans = min(ans, pos3[k] + len3 - pos1[i]);
    }
    return ans < INF ? ans : -1;
  }
};
