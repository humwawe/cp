#ifdef LC_LOCAL
#include<lc-util.h>
#endif


class Solution {
public:
  int countTrapezoids(vector<vector<int>> &points) {
    int n = points.size();

    unordered_map<int, unordered_map<int, unordered_map<int, vector<int>>>> mp;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++) {
        int xa = points[i][0], ya = points[i][1];
        int xb = points[j][0], yb = points[j][1];
        // 计算两点距离的平方
        int d2 = (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb);
        // 将两点式直线 (xa, ya) -- (xb, yb) 转为一般式方程 ax + by + c = 0
        // 这样 a / b 相同的直线就是互相平行的
        int a = yb - ya, b = xa - xb, c = xb * ya - xa * yb;
        // 统一正负号，否则我们会以为 (a, b) = (1, 2) 和 (a, b) = (-1, -2) 不是平行线
        if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0)) a = -a, b = -b, c = -c;
        // 约去公因数，否则我们会以为 (a, b) = (1, 2) 和 (a, b) = (2, 4) 不是平行线
        int g = gcd(gcd(abs(a), abs(b)), abs(c));
        a /= g;
        b /= g;
        c /= g;
        mp[a][b][c].push_back(d2);
      }

    int ans1 = 0, ans2 = 0;
    // 枚举直线方程里的 (a, b)，即枚举直线的斜率
    for (auto &pa: mp)
      for (auto &pb: pa.second) {
        // sm：从之前枚举过的平行线上选两个点的方案数
        int sm = 0;
        // cnt[d2]：从之前枚举过的平行线上选两个点，它们的距离平方等于 d2 的方案数
        unordered_map<int, int> cnt;
        // 枚举斜率为特定值的每条直线
        for (auto &pc: pb.second) {
          // 算梯形的数量
          ans1 += pc.second.size() * sm;
          sm += pc.second.size();
          unordered_map<int, int> tmp;
          for (int d2: pc.second) tmp[d2]++;
          // 算平行四边形的数量
          for (auto &p: tmp) {
            ans2 += p.second * cnt[p.first];
            cnt[p.first] += p.second;
          }
        }
      }
    assert(ans2 % 2 == 0);
    // 平行四边形两对边各算一次，所以要除以 2
    return ans1 - ans2 / 2;
  }
};
