#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  bool checkPrimeFrequency(vector<int> &nums) {

    auto check = [&](int x) {
      if (x == 1) return false;
      for (int i = 2; i * i <= x; i++) if (x % i == 0) return false;
      return true;
    };

    unordered_map<int, int> mp;
    for (int x: nums) mp[x]++;
    for (auto &p: mp) {
      if (check(p.second)) return true;
    }
    return false;
  }
};
