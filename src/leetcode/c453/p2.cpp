#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int countPermutations(vector<int> &complexity) {
    int n = complexity.size();
    long long res{1};
    int mod = 1e9 + 7;
    for (int i = 1; i < n; i++) {
      if (complexity[i] <= complexity[0]) {
        return 0;
      }
      res = res * i % mod;
    }
    return res;
  }
};
