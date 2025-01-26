#include <lc-util.h>

class Solution {
public:
  vector<int> countMentions(int n, vector<vector<string>> &events) {
    vector<int> vis(n), res(n);
    ranges::sort(events, [&](const auto &e1, const auto &e2) {
      if (e1[1] != e2[1]) return stoi(e1[1]) < stoi(e2[1]);
      return e1[0][0] > e2[0][0];
    });
    for (const auto &event: events) {
      string op = event[0];
      int tm = stoi(event[1]);
      if (op == "MESSAGE") {
        if (event[2] == "ALL") {
          for (int i = 0; i < n; ++i) {
            ++res[i];
          }
        } else if (event[2] == "HERE") {
          for (int i = 0; i < n; ++i) {
            if (tm >= vis[i]) {
              ++res[i];
            }
          }
        } else {
          int ptr = 0;
          while (ptr < event[2].size()) {
            int now = 0;
            for (; ptr < event[2].size() && !isdigit(event[2][ptr]); ++ptr);
            for (; ptr < event[2].size() && isdigit(event[2][ptr]); ++ptr) now = now * 10 + event[2][ptr] - 48;
            ++res[now];
          }
        }
      } else {
        int id = stoi(event[2]);
        vis[id] = tm + 60;
      }
    }
    return res;
  }
};
