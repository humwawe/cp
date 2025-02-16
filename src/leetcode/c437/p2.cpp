#include <lc-util.h>


class Solution {
public:
  long long maxWeight(vector<int> &pizzas) {
    ranges::sort(pizzas, greater());
    int n = pizzas.size() / 4;
    long long res{};
    int m = (n + 1) / 2;
    for (int i = 0; i < m; ++i) {
      res += pizzas[i];
    }
    for (int i = 0; i < n - m; i++) {
      res += pizzas[m + 2 * i + 1];
    }
    return res;
  }
};
