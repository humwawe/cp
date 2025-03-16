#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<int> longestCommonPrefix(vector<string> &words, int k) {
    int n = words.size();
    if (k >= n) {
      return vector<int>(n);
    }
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    ranges::sort(idx, [&](int i, int j) {
      return words[i] < words[j];
    });
    int m1{-1}, m2{-1}, p{-1};
    for (int i = 0; i + k - 1 < n; i++) {
      int j = i + k - 1;
      int l{};
      for (; l < min(words[idx[i]].size(), words[idx[j]].size()); l++) {
        if (words[idx[i]][l] != words[idx[j]][l]) {
          break;
        }
      }
      if (l > m1) {
        m2 = m1;
        m1 = l;
        p = i;
      } else if (l > m2) {
        m2 = l;
      }
    }
    vector<int> res(n);
    for (int i = 0; i < n; i++) {
      if (p <= i && i <= p + k - 1) {
        res[idx[i]] = m2;
      } else {
        res[idx[i]] = m1;
      }
    }
    return res;
  }
};
