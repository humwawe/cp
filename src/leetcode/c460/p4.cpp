#ifdef LC_LOCAL
#include<lc-util.h>
#endif


// 线性基模板
class XorBasis {
  vector<uint32_t> b;

public:
  XorBasis(int n) : b(n) {
  }

  void insert(uint32_t x) {
    while (x) {
      int i = bit_width(x) - 1; // x 的最高位
      if (b[i] == 0) {
        // x 和之前的基是线性无关的
        b[i] = x; // 新增一个基，最高位为 i
        return;
      }
      x ^= b[i]; // 保证参与 max_xor 的基的最高位是互不相同的，方便我们贪心
    }
    // 正常循环结束，此时 x=0，说明一开始的 x 可以被已有基表出，不是一个线性无关基
  }

  uint32_t max_xor() {
    uint32_t res = 0;
    // 从高到低贪心：越高的位，越必须是 1
    // 由于每个位的基至多一个，所以每个位只需考虑异或一个基，若能变大，则异或之
    for (int i = b.size() - 1; i >= 0; i--) {
      res = max(res, res ^ b[i]);
    }
    return res;
  }
};

class Solution {
public:
  long long maximizeXorAndXor(vector<int> &nums) {
    int n = nums.size();
    int sz = bit_width((uint32_t) ranges::max(nums));

    // 预处理所有子集的 AND 和 XOR（刷表法）
    int u = 1 << n;
    vector<int> sub_and(u), sub_xor(u);
    sub_and[0] = -1;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      int high_bit = 1 << i;
      for (int mask = 0; mask < high_bit; mask++) {
        sub_and[high_bit | mask] = sub_and[mask] & x;
        sub_xor[high_bit | mask] = sub_xor[mask] ^ x;
      }
    }
    sub_and[0] = 0;

    auto max_xor2 = [&](int sub) -> long long {
      XorBasis b(sz);
      int xor_ = sub_xor[sub];
      for (int i = 0; i < n; i++) {
        if (sub >> i & 1) {
          // 只考虑有偶数个 1 的比特位（xor 在这些比特位上是 0）
          b.insert(nums[i] & ~xor_);
        }
      }
      return xor_ + b.max_xor() * 2LL;
    };

    long long ans = 0;
    for (int i = 0; i < u; i++) {
      ans = max(ans, sub_and[i] + max_xor2((u - 1) ^ i));
    }
    return ans;
  }
};
