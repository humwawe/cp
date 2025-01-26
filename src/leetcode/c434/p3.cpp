#include<lc-util.h>

class Solution {
public:
  int maxFrequency(vector<int> &nums, int k) {
    int sum = 0;
    set<int> st;
    for (int num: nums) {
      if (num == k) {
        sum++;
      } else {
        st.insert(num);
      }
    }
    int gain = 0;
    for (int x: st) {
      int cur = 0;
      int t = 0;
      for (int num: nums) {
        if (num == x) {
          cur += 1;
        } else if (num == k) {
          cur -= 1;
        }

        t = max(t, cur);
        if (cur < 0) {
          cur = 0;
        }
      }

      gain = max(gain, t);
    }

    return sum + gain;
  }
};
