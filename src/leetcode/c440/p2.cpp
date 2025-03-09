#include <lc-util.h>

class Solution {
public:
  vector<long long> findMaxSum(vector<int> &nums1, vector<int> &nums2, int k) {
    map<int, vector<int>> mp;
    int n = nums1.size();
    for (int i = 0; i < n; i++) {
      mp[nums1[i]].push_back(i);
    }
    priority_queue<int, vector<int>, greater<>> pq;
    long long t{};
    vector<long long> res(n);
    for (auto &[_, v]: mp) {
      for (int i: v) {
        res[i] = t;
      }
      for (int i: v) {
        pq.push(nums2[i]);
        t += nums2[i];
        if (pq.size() > k) {
          t -= pq.top();
          pq.pop();
        }
      }
    }
    return res;
  }
};
