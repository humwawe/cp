#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  string generateTag(string caption) {
    istringstream ss(caption);
    string res = "#";
    string s;
    while (ss >> s) {
      for (auto &ch: s) {
        ch = tolower(ch);
      }
      if (res.size() > 1) {
        s[0] = toupper(s[0]);
      }
      res += s;
      if (res.size() >= 100) {
        res.resize(100);
        break;
      }
    }
    return res;
  }
};
