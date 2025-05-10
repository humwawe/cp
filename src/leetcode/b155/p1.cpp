#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  string findCommonResponse(vector<vector<string>> &responses) {
    map<string, int> mp;
    for (auto &response: responses) {
      set<string> vis{};
      for (auto &word: response) {
        if (vis.contains(word)) {
          continue;
        }
        vis.insert(word);
        mp[word]++;
      }
    }
    int t{};
    string res{};
    for (auto &[word, count]: mp) {
      if (count > t) {
        res = word;
        t = count;
      }
    }
    return res;
  }
};
