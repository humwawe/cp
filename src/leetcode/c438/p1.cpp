#include <lc-util.h>

class Solution {
public:
  bool hasSameDigits(string s) {
    int n = s.size();
    vector<int> a;
    for (int i = 0; i < n; i++) {
      a.push_back(s[i] - '0');
    }
    while (a.size() > 1) {
      vector<int> na;
      for (int i = 0; i < a.size() - 1; i++) {
        na.push_back((a[i] + a[i + 1]) % 10);
      }
      a = na;
    }
    return a[0] == a[1];
  }
};
