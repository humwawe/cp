#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int minStable(vector<int> &nums, int maxC) {
    int n = nums.size();

    // 预处理 ST 表
    const int MAXP = __lg(n);
    vector rmq(MAXP + 1, vector(n, 0));
    for (int i = 0; i < n; i++) rmq[0][i] = nums[i];
    for (int p = 1, len = 2; p <= MAXP; p++, len *= 2) {
      for (int i = 0, j = len - 1; j < n; i++, j++) {
        rmq[p][i] = gcd(rmq[p - 1][i], rmq[p - 1][i + len / 2]);
      }
    }

    // 求 nums[l..r] 的 gcd
    auto query = [&](int l, int r) {
      int p = __lg(r - l + 1);
      return gcd(rmq[p][l], rmq[p][r - (1 << p) + 1]);
    };

    // 检查能否通过至多 maxC 次修改，使得最长的稳定子数组长度不超过 lim
    auto check = [&](int lim) {
      if (lim == n) return true;
      int cnt = 0;
      // 枚举每个长度为 lim + 1 的子数组，它们的 gcd 都需要是 1
      for (int i = lim; i < n;) {
        int g = query(i - lim, i);
        if (g > 1) {
          // 如果 gcd 不是 1，把子数组最右边的元素改成 1，
          // 然后跳过所有包含这个元素的子数组
          cnt++;
          i += lim + 1;
        } else {
          i++;
        }
      }
      return cnt <= maxC;
    };

    int head = 0, tail = n;
    while (head < tail) {
      int mid = (head + tail) >> 1;
      if (check(mid)) tail = mid;
      else head = mid + 1;
    }
    return head;
  }
};
