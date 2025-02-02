#include <lc-util.h>

class Solution {
public:
  int maxDifference(string s) {
    vector cnt(26, 0);
    for (char c: s) {
      cnt[c - 'a']++;
    }
    int m1 = 0, m2 = 1005;
    for (int i = 0; i < 26; i++) {
      if (cnt[i] % 2 == 1) {
        m1 = max(m1, cnt[i]);
      } else if (cnt[i] > 0) {
        m2 = min(m2, cnt[i]);
      }
    }
    return m1 - m2;
  }
};
