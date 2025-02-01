#include <lc-util.h>


class Solution {
public:
  string findValidPair(string s) {
    map<char, int> mp;
    for (auto c: s) {
      mp[c]++;
    }

    for (int i = 0; i < s.length() - 1; i++) {
      if (s[i] != s[i + 1] && mp[s[i]] == s[i] - '0' && mp[s[i + 1]] == s[i + 1] - '0') {
        return s.substr(i, 2);
      }
    }
    return "";
  }
};
