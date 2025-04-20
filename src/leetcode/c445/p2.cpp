#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  string smallestPalindrome(string s) {
    int n = s.size();
    map<char, int> mp;
    for (int i = 0; i < n; i++) {
      mp[s[i]]++;
    }
    char c = '#';
    string res{};
    for (auto [k, v]: mp) {
      if (v % 2 == 1) {
        c = k;
      }
      for (int i = 0; i < v / 2; i++) {
        res += k;
      }
    }
    string t{res};
    ranges::reverse(t);
    if (c != '#') {
      res = res + c + t;
    } else {
      res = res + t;
    }
    return res;
  }
};
