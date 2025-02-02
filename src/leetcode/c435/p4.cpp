#include <lc-util.h>

class Solution {
public:
  int maxDifference(string s, int k) {
    int n = s.length();
    int inf = 1e9;
    function<int(int, int)> cal = [&](int a, int b)-> int {
      vector<array<int, 2>> st(n + 1);
      vector m_pre(4, inf);

      int x{}, y{}, lx{}, ly{};
      int res{-inf};
      int l = 0;
      for (int i = 0; i < n; i++) {
        if (s[i] - '0' == a) {
          x += 1;
        } else if (s[i] - '0' == b) {
          y += 1;
        }
        st[i + 1] = {x % 2 << 1 | y % 2, x - y};

        while (i - l >= k - 1 && x - lx > 0 && y - ly > 0) {
          m_pre[st[l][0]] = min(m_pre[st[l][0]], st[l][1]);
          if (s[l] - '0' == a) {
            lx += 1;
          } else if (s[l] - '0' == b) {
            ly += 1;
          }

          l += 1;
        }
        res = max(res, x - y - m_pre[st[i + 1][0] ^ 2]);

      }
      return res;
    };


    int res = -inf;
    for (int i = 0; i <= 4; i++) {
      for (int j = 0; j <= 4; j++) {
        if (i == j) continue;
        res = max(res, cal(i, j));
      }
    }
    return res;
  }
};

