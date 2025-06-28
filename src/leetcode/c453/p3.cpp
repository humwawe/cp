#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int countPartitions(vector<int> &nums, int k) {
    int n = nums.size();
    int mod = 1e9 + 7;
    vector<long long> f(n + 1), g(n + 1);
    f[0] = 1;
    g[0] = 1;
    int j{1};
    multiset<int> ms;
    for (int i = 1; i <= n; i++) {
      ms.insert(nums[i - 1]);
      while (j < i && *prev(ms.end()) - *ms.begin() > k) {
        ms.erase(ms.find(nums[j - 1]));
        j++;
      }
      f[i] = (g[i - 1] - (j - 2 >= 0 ? g[j - 2] : 0) + mod) % mod;
      g[i] = (g[i - 1] + f[i]) % mod;
    }
    return f[n];
  }
};
