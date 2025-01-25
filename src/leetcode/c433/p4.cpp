#include <lc-util.h>


class Solution {
public:
  long long minMaxSubarraySum(vector<int>& nums, int k) {
    auto sumSubarrayMins = [&]() -> long long {
      int n = nums.size();
      vector<int> left(n, -1);
      vector<int> right(n, n);
      stack<int> st;
      st.push(-1);
      for (int i = 0; i < n; i++) {
        int x = nums[i];
        while (st.size() > 1 && x <= nums[st.top()]) {
          right[st.top()] = i;
          st.pop();
        }
        left[i] = st.top();
        st.push(i);
      }

      long long res = 0;
      for (int i = 0; i < n; i++) {
        int x = nums[i], l = left[i], r = right[i];
        if (r - l - 1 <= k) {
          long long cnt = 1LL * (i - l) * (r - i);
          res += x * cnt;
        } else {
          l = max(l, i - k);
          r = min(r, i + k);
          // 左端点 > r-k 的子数组个数
          long long cnt = 1LL * (r - i) * (i - (r - k));
          // 左端点 <= r-k 的子数组个数
          long long cnt2 = 1LL * (l + r + k - i * 2 + 1) * (r - l - k) / 2;
          res += x * (cnt + cnt2);
        }
      }
      return res;
    };

    long long ans = sumSubarrayMins();
    // 所有元素取反，就可以复用同一份代码求最大值的贡献了
    for (int& x : nums) {
      x = -x;
    }
    ans -= sumSubarrayMins();
    return ans;
  }
};
