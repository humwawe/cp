#include <lc-util.h>

class Solution {
public:
  vector<int> permute(int n, long long k) {
    long long inf = 1e16;
    vector tmp(n + 1, inf);
    for (int i = 1; i < n + 1; i++) {
      int a = (i + 1) / 2;
      long long t = 1;
      if (i % 2 == 1) {
        for (long long j = 2; j <= a; j++) {
          t *= j * (j - 1);
        }
      } else {
        for (long long j = 2; j <= a; j++) {
          t *= j * j;
        }
      }
      tmp[i] = t;
      if (tmp[i] > inf) {
        break;
      }
    }

    if (n % 2 && tmp[n] < k) {
      return {};
    }
    if (n % 2 == 0 && tmp[n] * 2 < k) {
      return {};
    }

    vector vis(n + 2, 0), res(n, 0);

    auto nxt = [&](int i, int cur) {
      int s{cur + 1};
      for (; s <= n + 1; s++) {
        if (vis[s]) {
          continue;
        }
        if (i == 0) {
          if (n % 2 && s % 2 == 0) {
            continue;
          }
        } else {
          if (s % 2 == res[i - 1] % 2) {
            continue;
          }
        }

        break;
      }
      return s;
    };

    for (int i = 0; i < n; i++) {
      long long sum{};
      int cur = nxt(i, 0);
      while (sum + tmp[n - i - 1] < k) {
        sum += tmp[n - i - 1];
        cur = nxt(i, cur);
      }
      res[i] = cur;
      vis[cur] = 1;
      k -= sum;
    }

    return res;
  }
};
