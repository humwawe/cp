#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  vector<long long> resultArray(vector<int> &nums, int k) {
    int n = nums.size();
    vector<long long> res(k);
    vector f(n + 1, vector<int>(k));
    for (int i = 0; i < n; i++) {
      int v = nums[i] % k;
      f[i + 1][v] = 1;
      for (int y = 0; y < k; y++) {
        f[i + 1][y * v % k] += f[i][y];
      }
      for (int x = 0; x < k; x++) {
        res[x] += f[i + 1][x];
      }
    }
    return res;
  }
};
