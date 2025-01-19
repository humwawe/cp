#include <lc-util.h>

class Solution {
public:
  int distanceSum(int m, int n, int k) {
    int mod = 1e9 + 7;
    vector<long long> fac(n * m + 1);
    fac[0] = 1;
    for (int i = 1; i <= n * m; i++) fac[i] = fac[i - 1] * i % mod;
    vector<long long> ifac(n * m + 1);
    ifac[0] = ifac[1] = 1;
    for (int i = 2; i <= n * m; i++) ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
    for (int i = 2; i <= n * m; i++) ifac[i] = ifac[i - 1] * ifac[i] % mod;

    auto C = [&](int a, int b) {
      if (a < b) return 0LL;
      return fac[a] * ifac[b] % mod * ifac[a - b] % mod;
    };
    long long v = C(n * m - 2, k - 2);

    auto cal = [&](long long x, long long y) {
      long long res = 0;
      for (long long i = 1; i <= y - 1; i++) {
        res = (res + i * y - i * i) % mod;
      }
      return res * x % mod * x % mod * v % mod;
    };

    return (cal(m, n) + cal(n, m)) % mod;
  }
};
