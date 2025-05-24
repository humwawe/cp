#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int maxSubstrings(string word) {
    int n = word.size();
    vector<int> dp(n + 1);
    map<char, int> mp;
    for (int i = 1; i <= n; i++) {
      if (i >= 4) {
        mp[word[i - 4]] = i - 3;
      }
      dp[i] = dp[i - 1];
      if (mp.contains(word[i - 1])) {
        dp[i] = max(dp[i], dp[mp[word[i - 1]] - 1] + 1);
      }
    }
    return dp[n];
  }
};
