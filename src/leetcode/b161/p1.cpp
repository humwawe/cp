#ifdef LC_LOCAL
#include<lc-util.h>
#endif

const int MX = 100'000;
vector<bool> is_prime(MX);

auto init = [] {
  ranges::fill(is_prime, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i < MX; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j < MX; j += i) {
        is_prime[j] = false;
      }
    }
  }
  return 0;
}();

class Solution {
public:
  long long splitArray(vector<int> &nums) {
    long long ans = 0;
    for (int i = 0; i < nums.size(); i++) {
      ans += is_prime[i] ? nums[i] : -nums[i];
    }
    return abs(ans);
  }
};
