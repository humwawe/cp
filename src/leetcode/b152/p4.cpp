#include <lc-util.h>

class Solution {
public:
  vector<int> longestSpecialPath(vector<vector<int>> &edges, vector<int> &nums) {
    int n = edges.size() + 1;
    // 建图
    vector<int> e[n], v[n];
    for (auto &edge: edges) {
      e[edge[0]].push_back(edge[1]);
      v[edge[0]].push_back(edge[2]);
      e[edge[1]].push_back(edge[0]);
      v[edge[1]].push_back(edge[2]);
    }

    array<int, 2> ans = {-1, 0};
    // mp[c] 是一个 vector，保存了 DFS 过程中哪些深度出现了颜色 c，vector 的末尾是最大的深度
    unordered_map<int, vector<int>> mp;
    // vec[d] 保存了从根到深度为 d 的节点的路径长度
    vector<int> vec;
    // sm：根到当前节点（sn）的路径长度
    // lim1：最大的颜色重复深度
    // lim2：次大的颜色重复深度
    auto dfs = [&](this auto &&dfs, int sn, int fa, int sm, int lim1, int lim2) -> void {
      // 计算当前节点的深度
      int d = vec.size();
      // 把根到当前节点的路径长度压入栈，方便后续的 DFS 过程使用
      vec.push_back(sm);
      // DFS 栈中出现了和 sn 相同颜色的节点 u，更新 lim1 和 lim2 的值
      if (mp[nums[sn]].size() > 0) {
        int t = mp[nums[sn]].back() + 1;
        if (t > lim1) lim2 = lim1, lim1 = t;
        else if (t > lim2) lim2 = t;
      }
      // 计算从深度 lim2 到当前深度的路径长度和节点数量
      // 这里把节点数量取了负数，因为我们要最大化路径长度的同时，最小化节点数量
      ans = max(ans, {sm - vec[lim2], -(d - lim2 + 1)});
      // 把当前节点的颜色压入栈，方便后续的 DFS 过程使用
      mp[nums[sn]].push_back(vec.size() - 1);

      // DFS 进入子节点
      for (int i = 0; i < e[sn].size(); i++) {
        int fn = e[sn][i];
        if (fn == fa) continue;
        dfs(fn, sn, sm + v[sn][i], lim1, lim2);
      }

      // 当前节点退栈
      mp[nums[sn]].pop_back();
      vec.pop_back();
    };
    dfs(0, -1, 0, 0, 0);
    return {ans[0], -ans[1]};
  }
};
