#include <lc-util.h>


class Solution {
public:
  int maxDistance(string s, int k) {
    int n = s.length();
    map<char, char> mp;
    mp['N'] = 'S';
    mp['S'] = 'N';
    mp['E'] = 'W';
    mp['W'] = 'E';

    function<int(char, char)> cal = [&](char a, char b) {
      int x{}, y{}, res{};
      int change{};
      for (int i = 0; i < n; i++) {
        if (s[i] == a) {
          x++;
        } else if (s[i] == b) {
          y++;
        } else if (s[i] == mp[a]) {
          if (change < k) {
            x++;
            change++;
          } else {
            x--;
          }
        } else if (s[i] == mp[b]) {
          if (change < k) {
            y++;
            change++;
          } else {
            y--;
          }
        }
        res = max(res, abs(x) + abs(y));
      }
      return res;
    };

    int res = 0;
    for (auto a: "NS") {
      for (auto b: "EW") {
        res = max(res, cal(a, b));
      }
    }
    return res;
  }
};
