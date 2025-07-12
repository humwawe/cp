#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<int> longestCommonPrefix(vector<string> &words) {
    int n = words.size();
    vector<int> res;
    function<int(int, int)> cal = [&](int i, int j) {
      int k = 0;
      while (k < words[i].size() && k < words[j].size() && words[i][k] == words[j][k]) {
        k++;
      }
      return k;
    };
    multiset<int> tmp;
    vector<int> d;
    for (int i = 0; i < n - 1; i++) {
      int k = cal(i, i + 1);
      tmp.insert(k);
      d.push_back(k);
    }


    for (int i = 0; i < n; i++) {
      if (i > 0) {
        tmp.erase(tmp.find(d[i - 1]));
      }
      if (i < n - 1) {
        tmp.erase(tmp.find(d[i]));
      }

      if (i - 1 >= 0 && i + 1 < n) {
        int x = cal(i - 1, i + 1);
        tmp.insert(x);
      }

      if (tmp.empty()) {
        res.push_back(0);
      } else {
        res.push_back(*tmp.rbegin());
      }


      if (i > 0) {
        tmp.insert(d[i - 1]);
      }
      if (i < n - 1) {
        tmp.insert(d[i]);
      }

      if (i - 1 >= 0 && i + 1 < n) {
        int x = cal(i - 1, i + 1);
        tmp.erase(tmp.find(x));
      }
    }
    return res;
  }
};
