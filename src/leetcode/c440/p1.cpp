#include <lc-util.h>

class Solution {
public:
  int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets) {
    int n = fruits.size();
    int res{};
    vector<int> vis(n);
    for (int i = 0; i < n; i++) {
      bool f{};
      for (int j = 0; j < n; j++) {
        if (vis[j]) {
          continue;
        }
        if (baskets[j] >= fruits[i]) {
          vis[j] = 1;
          f = true;
          break;
        }
      }
      if (!f) {
        res++;
      }
    }
    return res;
  }
};
