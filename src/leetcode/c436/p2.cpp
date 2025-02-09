#include <lc-util.h>


class Solution {
public:
  vector<int> assignElements(vector<int> &groups, vector<int> &elements) {
    unordered_map<int, vector<int>> mp;

    int n = groups.size();
    for (int i = 0; i < n; i++) {
      mp[groups[i]].push_back(i);
    }
    int m = ranges::max(groups);

    vector res(n, -1);
    unordered_set<int> used;

    for (int j = 0; j < elements.size(); j++) {
      if (used.contains(elements[j])) {
        continue;
      }
      for (int v = elements[j]; v <= m; v += elements[j]) {
        if (mp.contains(v)) {
          for (int i: mp[v]) {
            res[i] = j;
          }
        }
        mp.erase(v);
      }
      used.insert(elements[j]);
    }
    return res;
  }
};
