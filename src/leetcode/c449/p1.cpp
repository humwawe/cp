#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  int minDeletion(string s, int k) {
    map<int, int> mp;
    for (auto c: s) {
      mp[c]++;
    }
    vector<int> tmp;
    for (auto [k,v]: mp) {
      tmp.push_back(v);
    }
    ranges::sort(tmp, ranges::greater{});
    int res{};
    for (int i = k; i < tmp.size(); i++) {
      res += tmp[i];
    }
    return res;
  }
};
