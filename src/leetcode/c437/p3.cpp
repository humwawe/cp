#include<lc-util.h>


class Solution {
public:
  bool maxSubstringLength(string s, int K) {
    int n = s.size();

    vector<int> pos[26];
    for (int i = 0; i < n; i++) {
      int c = s[i] - 'a';
      pos[c].push_back(i);
    }

    typedef pair<int, int> pii;
    vector<pii> vec;
    for (auto &po: pos)
      if (!po.empty()) {
        int l = po[0], r = po.back();
        bool flag = true;
        while (flag) {
          flag = false;
          for (auto &j: pos) {
            int cnt = ranges::upper_bound(j, r) - ranges::lower_bound(j, l);
            if (cnt > 0 && cnt < j.size()) {
              l = min(l, j[0]);
              r = max(r, j.back());
              flag = true;
            }
          }
        }
        if (l > 0 || r < n - 1) {
          vec.emplace_back(r, l);
        }
      }

    ranges::sort(vec);
    int R = -1, cnt = 0;
    for (pii p: vec)
      if (p.second > R) {
        R = p.first;
        cnt++;
      }
    return cnt >= K;
  }
};
