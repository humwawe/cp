#include <lc-util.h>

class Solution {
public:
  int totalNumbers(vector<int> &digits) {
    vector<int> cnt(10);
    for (int digit: digits) {
      cnt[digit]++;
    }
    int res{};
    for (int i = 1; i <= 9; i++) {
      for (int j = 0; j <= 9; j++) {
        for (int k = 0; k <= 9; k += 2) {
          vector<int> c(10);
          c[i]++;
          c[j]++;
          c[k]++;
          if (c[i] <= cnt[i] && c[j] <= cnt[j] && c[k] <= cnt[k]) {
            res++;
          }
        }
      }
    }
    return res;
  }
};
