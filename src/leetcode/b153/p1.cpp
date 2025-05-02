#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


class Solution {
public:
  int reverseDegree(string s) {
    int n = s.size();
    int res{};
    for (int i = 0; i < n; i++) {
      res += (26 - (s[i] - 'a')) * (i + 1);
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  Solution s;

  debug(s.reverseDegree("abc"));
  cout << s.reverseDegree("abc") << endl;
}
