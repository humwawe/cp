#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif

class Solution {
public:
  int maxActiveSectionsAfterTrade(string s) {
    int n = s.size();
    vector<int> t;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0') {
        int j = i;
        while (j < n && s[j] == '0') {
          j++;
        }
        t.push_back(j - i);
        i = j - 1;
      }
    }

    int tmp{};

    for (int i = 1; i < t.size(); i++) {
      tmp = max(tmp, t[i - 1] + t[i]);
    }

    return ranges::count(s, '1') + tmp;
  }
};