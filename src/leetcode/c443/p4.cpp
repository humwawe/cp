#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif
// 模板：求滑动窗口的中位数

struct Magic {
  // st1：窗口内较小一半的数
  // st2：窗口内较大一半的数
  multiset<long long> st1, st2;
  // st1 和 st2 里的元素和
  long long sm1, sm2;

  Magic() {
    sm1 = 0;
    sm2 = 0;
  }

  // 调整两个对顶 set，使得元素数量恰好是 floor(窗口长度 / 2) 以及 ceil(窗口长度 / 2)
  void adjust() {
    int tot = st1.size() + st2.size();
    int a = tot / 2, b = tot - a;
    while (st1.size() < a) {
      long long t = *(st2.begin());
      st1.insert(t);
      sm1 += t;
      st2.erase(st2.begin());
      sm2 -= t;
    }
    while (st2.size() < b) {
      long long t = *prev(st1.end());
      st2.insert(t);
      sm2 += t;
      st1.erase(prev(st1.end()));
      sm1 -= t;
    }
  }

  // 把 x 加入滑动窗口
  void add(long long x) {
    if (!st2.empty() && x >= *(st2.begin())) st2.insert(x), sm2 += x;
    else st1.insert(x), sm1 += x;
    adjust();
  }

  // 从滑动窗口删除 x
  void del(long long x) {
    auto it = st1.find(x);
    if (it != st1.end()) st1.erase(it), sm1 -= x;
    else st2.erase(st2.find(x)), sm2 -= x;
    adjust();
  }

  // 求窗口内所有数变得相等的最小代价
  long long query() {
    // 先求出中位数
    long long mid = *(st2.begin());
    // 再把所有数变成中位数
    return (st1.size() * mid - sm1) + (sm2 - st2.size() * mid);
  }
};

class Solution {
public:
  long long minOperations(vector<int> &nums, int m, int k) {
    int n = nums.size();

    const long long inf = 1e18;
    vector f(n + 1, vector<long long>(k + 1, inf));
    f[0][0] = 0;

    Magic magic;
    for (int i = 1; i <= n; i++) {
      magic.add(nums[i - 1]);
      for (int j = 0; j <= k; j++) {
        f[i][j] = min(f[i][j], f[i - 1][j]);
        if (j > 0 && i >= m) {
          f[i][j] = min(f[i][j], f[i - m][j - 1] + magic.query());
        }
      }
      if (i >= m) magic.del(nums[i - m]);
    }
    return f[n][k];
  }
};
