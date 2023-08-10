#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
int n, q;
int mx[N];
bool np[N];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  cin >> n >> q;
  for (int i = 2; i <= n; i++) {
    if (!np[i]) {
      mx[i] = i;
      for (int j = 2 * i; j <= n; j += i) {
        mx[j] = i, np[j] = 1;
      }
    }
  }

  while (q--) {
    int x, y, ans = 0;
    cin >> x >> y;
    while (x != y) {
      if (x < y) {
        swap(x, y);
      }
      x /= mx[x], ans++;
    }

    cout << ans << '\n';
  }
}
