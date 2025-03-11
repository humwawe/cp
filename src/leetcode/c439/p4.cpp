#include <lc-util.h>

class Solution {
public:
  string generateString(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    string ans;
    ans.resize(n + m - 1);

    vector<bool> flag(n + m - 1);
    for (int i = 0; i < n; i++) {
      if (str1[i] == 'T') {
        for (int j = 0; j < m; j++)
          ans[i + j] = str2[j], flag[i + j] = true;
      }
    }

    for (int i = 0; i < n; i++)
      if (str1[i] == 'T') {
        if (ans.substr(i, m) != str2) return "";
      }

    for (char &c: ans) {
      if (c == 0) c = 'a';
    }

    for (int i = 0; i < n; i++)
      if (str1[i] == 'F' && ans.substr(i, m) == str2) {
        bool failed = true;
        for (int j = m - 1; j >= 0; j--)
          if (!flag[i + j]) {
            ans[i + j] = 'b';
            failed = false;
            break;
          }

        if (failed) return "";
      }
    return ans;
  }
};
