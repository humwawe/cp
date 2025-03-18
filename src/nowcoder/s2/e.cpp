#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--) {
    int a, b, c;
    cin >> a >> b >> c;
    int res{6};
    if (a + b > c) {
      res++;
    }
    if (2 * a > b) {
      res++;
    }
    if (2 * a > c) {
      res++;
    }
    if (2 * b > c) {
      res++;
    }
    cout << res << endl;
  }
}
