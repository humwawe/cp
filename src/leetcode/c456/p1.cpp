#ifdef LC_LOCAL
#include<lc-util.h>
#endif

// 字符串哈希模板开始

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y) {
  return uniform_int_distribution<int>(x, y)(rng);
}

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
  vector<__int128> P, H;

  HashSeq(string &s) {
    int n = s.size();
    P.resize(n + 1);
    P[0] = 1;
    for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
    H.resize(n + 1);
    H[0] = 0;
    for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
  }

  long long query(int l, int r) {
    return (H[r] - H[l - 1] * P[r - l + 1] % MOD + MOD) % MOD;
  }
};

// 字符串哈希模板结束

class Solution {
public:
  vector<string> partitionString(string s) {
    int n = s.size();
    HashSeq hs(s);

    vector<string> ans;
    // st[len]：出现过哪些长度为 len 的子串的哈希值
    unordered_set<long long> st[n + 1];
    // 当前子串下标范围是 [j, i]
    for (int i = 1, j = 1; i <= n; i++) {
      int len = i - j + 1;
      long long h = hs.query(j, i);
      if (st[len].count(h) == 0) {
        st[len].insert(h);
        ans.push_back(s.substr(j - 1, len));
        j = i + 1;
      }
    }
    return ans;
  }
};
