#include <bits/stdc++.h>

using namespace std;

const int N = 305, V = 128, mod = 998244353;
int n, m, a[N][N];
int f[N][N][V][2];

int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  f[0][1][0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 0; k != V; k++) {
        f[i][j][k][0] = add(f[i - 1][j][k ^ a[i][j]][0], f[i][j - 1][k ^ a[i][j]][0]);
        f[i][j][k][1] = add(f[i - 1][j][k ^ a[i][j]][1], f[i][j - 1][k ^ a[i][j]][1]);
        f[i][j][k][1] = add(f[i][j][k][1], add(f[i - 1][j][k][0], f[i][j - 1][k][0]));
      }
    }
  }

  int ans = 0;
  for (int i = 0; i != V; i++) {
    ans = (ans + 1ll * i * f[n][m][i][1]) % mod;
  }
  cout << ans << endl;
}
