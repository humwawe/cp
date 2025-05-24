#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  long long sumOfLargestPrimes(string s) {
    int n = s.size();
    function<bool(long long)> check = [](long long x) {
      if (x == 1) return false;
      for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) {
          return false;
        }
      }
      return true;
    };

    set<long long> st;
    for (int i = 0; i < n; i++) {
      long long t = 0;
      for (int j = i; j < n; j++) {
        t = t * 10 + s[j] - '0';
        if (check(t)) {
          st.insert(t);
        }
      }
    }
    vector<long long> cur;
    for (long long x: st) {
      cur.push_back(x);
    }
    ranges::sort(cur, greater<long long>{});
    long long res{};
    for (int i = 0; i < min(3, (int) cur.size()); i++) {
      res += cur[i];
    }
    return res;
  }
};
