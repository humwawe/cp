#include <lc-util.h>

class Solution {
public:
  bool hasSpecialSubstring(string s, int k) {
    int n = s.size();
    for (int i = 0; i <= n - k; ++i) {
      string tmp = s.substr(i, k);
      if (ranges::count(tmp, tmp[0]) == k) {
        if (i - 1 >= 0 && s[i - 1] == s[i]) {
          continue;
        }
        if (i + k < n && s[i + k] == s[i]) {
          continue;
        }
        return true;
      }
    }
    return false;
  }
};
