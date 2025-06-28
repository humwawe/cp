#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class LcaBinaryLifting {
public:
  vector<int> depth;
  vector<long long> dis;
  vector<vector<int>> pa;

  LcaBinaryLifting(vector<vector<int>> &edges) {
    int n = edges.size() + 1;
    int m = bit_width((unsigned) n); // n 的二进制长度
    vector<vector<pair<int, int>>> g(n);
    for (auto &e: edges) {
      int x = e[0], y = e[1], w = e[2];
      g[x].emplace_back(y, w);
      g[y].emplace_back(x, w);
    }

    depth.resize(n);
    dis.resize(n);
    pa.resize(n, vector<int>(m, -1));

    auto dfs = [&](this auto &&dfs, int x, int fa) -> void {
      pa[x][0] = fa;
      for (auto &[y, w]: g[x]) {
        if (y != fa) {
          depth[y] = depth[x] + 1;
          dis[y] = dis[x] + w;
          dfs(y, x);
        }
      }
    };
    dfs(0, -1);

    for (int i = 0; i < m - 1; i++) {
      for (int x = 0; x < n; x++) {
        if (int p = pa[x][i]; p != -1) {
          pa[x][i + 1] = pa[p][i];
        }
      }
    }
  }

  int get_kth_ancestor(int node, int k) {
    for (; k; k &= k - 1) {
      node = pa[node][countr_zero((unsigned) k)];
    }
    return node;
  }

  // 返回 x 和 y 的最近公共祖先（节点编号从 0 开始）
  int get_lca(int x, int y) {
    if (depth[x] > depth[y]) {
      swap(x, y);
    }
    y = get_kth_ancestor(y, depth[y] - depth[x]); // 使 y 和 x 在同一深度
    if (y == x) {
      return x;
    }
    for (int i = pa[x].size() - 1; i >= 0; i--) {
      int px = pa[x][i], py = pa[y][i];
      if (px != py) {
        x = px;
        y = py; // 同时往上跳 2^i 步
      }
    }
    return pa[x][0];
  }

  // 返回 x 到 y 的距离（最短路长度）
  long long get_dis(int x, int y) {
    return dis[x] + dis[y] - dis[get_lca(x, y)] * 2;
  }

  // 从 x 往上跳【至多】d 距离，返回最远能到达的节点
  int upto_dis(int x, long long d) {
    long long dx = dis[x];
    for (int i = pa[x].size() - 1; i >= 0; i--) {
      int p = pa[x][i];
      if (p != -1 && dx - dis[p] <= d) {
        // 可以跳至多 d
        x = p;
      }
    }
    return x;
  };
};

class Solution {
public:
  vector<int> findMedian(int n, vector<vector<int>> &edges, vector<vector<int>> &queries) {
    LcaBinaryLifting g(edges);

    vector<int> ans;
    ans.reserve(queries.size());
    for (auto &q: queries) {
      int x = q[0], y = q[1];
      if (x == y) {
        ans.push_back(x);
        continue;
      }
      int lca = g.get_lca(x, y);
      long long dis_xy = g.dis[x] + g.dis[y] - g.dis[lca] * 2;
      long long half = (dis_xy + 1) / 2;
      int res;
      if (g.dis[x] - g.dis[lca] >= half) {
        int to = g.upto_dis(x, half - 1);
        res = g.pa[to][0];
      } else {
        res = g.upto_dis(y, dis_xy - half);
      }
      ans.push_back(res);
    }
    return ans;
  }
};
