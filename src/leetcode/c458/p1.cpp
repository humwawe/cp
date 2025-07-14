#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  string processStr(string s) {
    string ans;
    for (char c: s) {
      if (c == '*') {
        if (!ans.empty()) {
          ans.pop_back();
        }
      } else if (c == '#') {
        ans += ans;
      } else if (c == '%') {
        ranges::reverse(ans);
      } else {
        ans += c;
      }
    }
    return ans;
  }
};
