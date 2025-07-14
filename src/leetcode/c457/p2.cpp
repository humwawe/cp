#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  vector<int> processQueries(int n, vector<vector<int>> &connections, vector<vector<int>> &queries) {
    int root[n + 1];
    // 求并查集的根
    auto findroot = [&](this auto &&findroot, int x) -> int {
      if (root[x] != x) root[x] = findroot(root[x]);
      return root[x];
    };

    // 构建电网
    for (int i = 1; i <= n; i++) root[i] = i;
    for (auto &edge: connections) {
      int x = findroot(edge[0]), y = findroot(edge[1]);
      if (x != y) root[x] = y;
    }

    // 对每个电网用一个 set 维护当前在线的电站
    set<int> st[n + 1];
    for (int i = 1; i <= n; i++) st[findroot(i)].insert(i);

    vector<int> ans;
    for (auto &qry: queries) {
      int r = findroot(qry[1]);
      if (qry[0] == 1) {
        // 该电站未离线
        if (st[r].contains(qry[1])) ans.push_back(qry[1]);
          // 该电站已离线，但电网里还有未离线的电站，取最小值
        else if (st[r].size() > 0) ans.push_back(*st[r].begin());
          // 电网里的电站都离线了
        else ans.push_back(-1);
      } else {
        // 将电站离线
        st[r].erase(qry[1]);
      }
    }
    return ans;
  }
};
