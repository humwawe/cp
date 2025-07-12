#ifdef LC_LOCAL
#include<lc-util.h>
#endif


#define MAXX ((int) 5e4)
bool inited = false, flag[MAXX + 5];

void init() {
  if (inited) return;
  inited = true;
  flag[1] = true;
  for (int i = 2; i * i <= MAXX; i++) {
    if (!flag[i]) {
      for (int j = i * 2; j <= MAXX; j += i) {
        flag[j] = true;
      }
    }
  }
}

class Solution {
public:
  int primeSubarray(vector<int> &nums, int K) {
    init();

    int n = nums.size();
    for (auto &x: nums) {
      if (flag[x]) x = 0;
    }

    int ans = 0, cnt = 0;
    multiset<int> ms;

    for (int i = 0, j1 = 0, j2 = 0; i < n; i++) {
      if (nums[i] > 0) {
        cnt++;
        ms.insert(nums[i]);
      }
      while (j1 < i && cnt > 1) {
        if (nums[j1] > 0) cnt--;
        j1++;
      }
      while (j2 < i && !ms.empty() && *ms.rbegin() - *ms.begin() > K) {
        if (nums[j2] > 0) {
          ms.erase(ms.find(nums[j2]));
        }
        j2++;
      }
      ans += j1 - j2;
    }
    return ans;
  }
};
