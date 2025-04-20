#ifdef LC_LOCAL
#include<lc-util.h>
#endif

int mod = 1e9 + 7;

vector<int> trans(string &s, int b) {
  for (char &c: s) {
    c -= '0';
  }
  vector<int> digits;
  while (!s.empty()) {
    string nxt_s;
    int rem = 0;
    for (char c: s) {
      rem = rem * 10 + c;
      int q = rem / b;
      if (q || !nxt_s.empty()) {
        nxt_s.push_back(q);
      }
      rem = rem % b;
    }
    digits.push_back(rem);
    s = move(nxt_s);
  }
  ranges::reverse(digits);
  return digits;
}


long long solve(string x, int b) {
  vector<int> nums = trans(x, b);

  int n = nums.size();
  vector memo(n, vector(b, -1ll));

  function<long long(int, int, bool, bool)> dfs = [&](int i, int pre, bool limit, bool lead) {
    if (i == n) {
      return 1ll;
    }
    if (!limit && !lead && memo[i][pre] != -1) {
      return memo[i][pre];
    }

    long long res = 0;
    if (lead) {
      res = dfs(i + 1, pre, false, true);
    }

    int up = limit ? nums[i] : b - 1;
    int low = lead ? 1 : 0;

    for (int j = max(low, pre); j <= up; j++) {
      res += dfs(i + 1, j, limit && j == up, false);
      res %= mod;
    }
    if (!limit && !lead) {
      memo[i][pre] = res;
    }
    return res;
  };

  return dfs(0, 0, true, true);
}


class Solution {
public:
  int countNumbers(string l, string r, int b) {
    string ll = l;
    vector<int> low = trans(ll, b);
    int t = 1;
    for (int i = 1; i < low.size(); i++) {
      if (low[i] < low[i - 1]) {
        t = 0;
      }
    }
    return (solve(r, b) - solve(l, b) + t + mod) % mod;
  }
};
