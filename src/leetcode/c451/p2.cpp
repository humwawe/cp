#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  string resultingString(string s) {
    string st;
    int n = s.size();
    for (int i = 0; i < n; i++) {
      if (!st.empty() && (abs(s[i] - st.back()) == 1 || abs(s[i] - st.back()) == 25)) {
        st.pop_back();
        continue;
      }
      st.push_back(s[i]);
    }

    return st;
  }
};