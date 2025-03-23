#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  long long minTime(vector<int> &skill, vector<int> &mana) {
    int n = skill.size(), m = mana.size();
    vector<long long> t(n);
    for (int i = 0; i < m; ++i) {
      vector<long long> nt(n);
      long long add = 0;
      for (int j = 0; j < n; ++j) {
        if (j == 0) {
          nt[j] = t[j] + mana[i] * skill[j];
        } else {
          nt[j] = nt[j - 1] + mana[i] * skill[j];
        }
        if (j + 1 < n && nt[j] < t[j + 1]) {
          add = max(add, t[j + 1] - nt[j]);
        }
      }
      for (int j = 0; j < n; ++j) {
        nt[j] += add;
      }
      t = nt;

    }
    return t[n - 1];
  }
};
