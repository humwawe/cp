#ifdef LC_LOCAL
#include<lc-util.h>
#include "debug.h"
#endif


struct HLD {
  int n;
  vector<int> siz, top, dep, parent, in, out, seq;
  vector<vector<int>> adj;
  int cur;

  HLD() {
  }

  HLD(int n) {
    init(n);
  }

  void init(int n) {
    this->n = n;
    siz.resize(n);
    top.resize(n);
    dep.resize(n);
    parent.resize(n);
    in.resize(n);
    out.resize(n);
    seq.resize(n);
    cur = 0;
    adj.assign(n, {});
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void work(int root = 0) {
    top[root] = root;
    dep[root] = 0;
    parent[root] = -1;
    dfs1(root);
    dfs2(root);
  }

  void dfs1(int u) {
    if (parent[u] != -1) {
      adj[u].erase(ranges::find(adj[u], parent[u]));
    }

    siz[u] = 1;
    for (auto &v: adj[u]) {
      parent[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]]) {
        swap(v, adj[u][0]);
      }
    }
  }

  void dfs2(int u) {
    in[u] = cur++;
    seq[in[u]] = u;
    for (auto v: adj[u]) {
      top[v] = v == adj[u][0] ? top[u] : v;
      dfs2(v);
    }
    out[u] = cur;
  }

  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = parent[top[u]];
      } else {
        v = parent[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

  int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }

  int jump(int u, int k) {
    if (dep[u] < k) {
      return -1;
    }

    int d = dep[u] - k;

    while (dep[top[u]] > d) {
      u = parent[top[u]];
    }

    return seq[in[u] - dep[u] + d];
  }

  bool isAncester(int u, int v) {
    return in[u] <= in[v] && in[v] < out[u];
  }

  int rootedParent(int u, int v) {
    swap(u, v);
    if (u == v) {
      return u;
    }
    if (!isAncester(u, v)) {
      return parent[u];
    }
    auto it = ranges::upper_bound(adj[u], v, [&](int x, int y) {
      return in[x] < in[y];
    }) - 1;
    return *it;
  }

  int rootedSize(int u, int v) {
    if (u == v) {
      return n;
    }
    if (!isAncester(v, u)) {
      return siz[v];
    }
    return n - siz[rootedParent(u, v)];
  }

  int rootedLca(int a, int b, int c) {
    return lca(a, b) ^ lca(b, c) ^ lca(c, a);
  }
};

class Solution {
public:
  vector<int> minimumWeight(vector<vector<int>> &edges, vector<vector<int>> &queries) {
    int n = edges.size() + 1;
    HLD hld(n);
    vector<vector<array<int, 2>>> g(n);
    for (auto &e: edges) {
      hld.addEdge(e[0], e[1]);
      g[e[0]].push_back({e[1], e[2]});
      g[e[1]].push_back({e[0], e[2]});
    }
    hld.work();
    vector<int> dist(n);
    function<void(int, int)> dfs = [&](int u, int p) {
      for (auto &[v, w]: g[u]) {
        if (v == p) {
          continue;
        }
        dist[v] = dist[u] + w;
        dfs(v, u);
      }
    };
    dfs(0, 0);

    function<int(int, int)> dis = [&](int x, int y) {
      return dist[x] + dist[y] - 2 * dist[hld.lca(x, y)];
    };

    vector<int> res(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
      int u = queries[i][0], v = queries[i][1], d = queries[i][2];
      int l1 = hld.lca(u, v);
      int l2 = hld.lca(u, d);
      int l3 = hld.lca(v, d);
      int l = l1;
      if (hld.dep[l2] > hld.dep[l]) {
        l = l2;
      }
      if (hld.dep[l3] > hld.dep[l]) {
        l = l3;
      }
      res[i] = dis(u, d) + dis(v, d) - dis(l, d);
    }
    return res;
  }
};
