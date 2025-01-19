#include<lc-util.h>

class Solution {
public:
  vector<int> longestSpecialPath(vector<vector<int>> &edges, vector<int> &nums) {
    int n = nums.size();
    vector<vector<pair<int, int>>> g(n);
    for (auto &e: edges) {
      int x = e[0], y = e[1], w = e[2];
      g[x].emplace_back(y, w);
      g[y].emplace_back(x, w);
    }

    pair ans = {-1, 0};
    vector dis = {0};
    unordered_map<int, int> last_depth;

    auto dfs = [&](auto &self, int x, int fa, int top_depth) -> void {
      int color = nums[x];
      int old_depth = last_depth[color];
      top_depth = max(top_depth, old_depth);
      ans = max(ans, pair(dis.back() - dis[top_depth], top_depth - (int) dis.size()));

      last_depth[color] = dis.size();
      for (auto &[y, w]: g[x]) {
        if (y != fa) {
          dis.push_back(dis.back() + w);
          self(self, y, x, top_depth);
          dis.pop_back();
        }
      }
      last_depth[color] = old_depth;
    };

    dfs(dfs, 0, -1, 0);
    return {ans.first, -ans.second};
  }
};
