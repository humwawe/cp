#ifdef LC_LOCAL
#include<lc-util.h>
#endif

class Solution {
public:
  vector<string> validateCoupons(vector<string> &code, vector<string> &businessLine, vector<bool> &isActive) {
    int n = code.size();

    // 判断字符串是否非空，且仅有大小写字母、数字和下划线构成
    auto check1 = [&](string &s) {
      if (s.size() == 0) return false;
      for (char c: s) {
        if (c >= 'a' && c <= 'z') continue;
        if (c >= 'A' && c <= 'Z') continue;
        if (c >= '0' && c <= '9') continue;
        if (c == '_') continue;
        return false;
      }
      return true;
    };

    // 判断业务类别是否合法
    auto check2 = [&](string &s) {
      return s == "electronics" || s == "grocery" || s == "pharmacy" || s == "restaurant";
    };

    typedef pair<string, string> pss;
    vector<pss> vec;
    for (int i = 0; i < n; i++) {
      if (check1(code[i]) && check2(businessLine[i]) && isActive[i]) {
        vec.push_back({businessLine[i], code[i]});
      }
    }

    // 排序时的业务类别刚好是按字典序的，所以我们可以直接排序
    ranges::sort(vec);
    vector<string> ans;
    for (auto &p: vec) ans.push_back(p.second);
    return ans;
  }
};
