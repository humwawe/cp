#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxFreqSum(string s) {
    string ys = "aeiou";
    int res1{}, res2{};
    map<char, int> mp;
    for (auto c: s) {
      mp[c]++;
    }
    for (auto [k,v]: mp) {
      if (ys.contains(k)) {
        res1 = max(res1, v);
      } else {
        res2 = max(res2, v);
      }
    }
    return res1 + res2;
  }
};
