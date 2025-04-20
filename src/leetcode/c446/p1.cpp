#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  long long calculateScore(vector<string>& instructions, vector<int>& values) {
    int n = instructions.size();
    vector<int> vis(n);
    long long res = 0;
    int i = 0;
    while (0 <= i && i < n && !vis[i]) {
      vis[i] = true;
      if (instructions[i][0] == 'a') {
        res += values[i];
        i++;
      } else {
        i += values[i];
      }
    }
    return res;
  }
};

