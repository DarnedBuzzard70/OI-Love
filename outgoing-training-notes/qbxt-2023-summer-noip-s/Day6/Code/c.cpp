#include <bits/stdc++.h>

using namespace std;

int n, ans;

int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    ans += (2 * n - i) / i - 1;
    if (i & 1) {
      ans -= (2 * n - i) / (2 * i);
    }
  }
  cout << ans << endl;
}
