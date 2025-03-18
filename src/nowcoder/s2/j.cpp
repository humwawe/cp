#include<bits/stdc++.h>
using namespace std;

void solve(int a, int b) {
  bool f{};
  for (int i = 2; i < max(a, b); ++i) {
    if (gcd(a, i) == 1 && gcd(b, i) == 1) {
      cout << i << endl;
      f = true;
      break;
    }
  }
  if (!f) {
    cout << -1 << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int a, b;
    cin >> a >> b;
    solve(a, b);
  }
}
