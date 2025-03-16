#include <lc-util.h>

class Solution {
public:
  long long maxSubarrays(int n, vector<vector<int>> &conflictingPairs) {
    vector<vector<int>> groups(n + 1);
    for (auto &p: conflictingPairs) {
      int a = p[0], b = p[1];
      if (a > b) {
        swap(a, b);
      }
      groups[a].push_back(b);
    }

    long long ans = 0;
    vector<long long> extra(n + 2);
    vector<int> b = {n + 1, n + 1}; // 维护最小 b 和次小 b
    for (int a = n; a > 0; a--) {
      auto &list_b = groups[a];
      b.insert(b.end(), list_b.begin(), list_b.end());
      ranges::sort(b);
      b.resize(2);
      ans += b[0] - a;
      extra[b[0]] += b[1] - b[0];
    }

    return ans + ranges::max(extra);
  }
};
