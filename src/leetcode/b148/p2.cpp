#include <lc-util.h>

class Solution {
public:
  long long minCost(vector<int> &arr, vector<int> &brr, long long k) {
    int n = arr.size();
    long long sum = 0;
    for (int i = 0; i < n; i++) {
      sum += abs(arr[i] - brr[i]);
    }
    long long res = sum;
    ranges::sort(arr);
    ranges::sort(brr);
    sum = 0;
    for (int i = 0; i < n; i++) {
      sum += abs(arr[i] - brr[i]);
    }
    res = min(res, sum + k);
    return res;
  }
};
