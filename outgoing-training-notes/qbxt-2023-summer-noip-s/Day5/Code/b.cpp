#include <bits/stdc++.h>

using namespace std;

const int N = 5005, mod = 1e9 + 7;
int n, f[N][N], g[N][N], ans;
vector<int> to[N];

int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }

void dfs(int i, int fa) {
  f[i][i] = g[i][i] = 1;

  for (int j : to[i]) {
    if (j == fa) {
      continue;
    }

    dfs(j, i);

    for (int k = 1, s1 = 0, s2 = 0; k <= n; k++) {
      ans = (ans + 1ll * s1 * g[j][k] + 1ll * s2 * g[i][k]) % mod;
      s1 = add(s1, f[i][k]), s2 = add(s2, f[j][k]);
    }

    for (int k = 1; k != i; k++) {
      f[i][i] = add(f[i][i], f[j][k]);
    }
    for (int k = n; k != i; k--) {
      g[i][i] = add(g[i][i], g[j][k]);
    }

    for (int k = 1; k <= n; k++) {
      f[i][k] = add(f[i][k], f[j][k]);
      g[i][k] = add(g[i][k], g[j][k]);
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  cin >> n;
  for (int i = 1; i != n; i++) {
    int x, y;
    cin >> x >> y;
    to[x].push_back(y), to[y].push_back(x);
  }

  dfs(1, 0);

  cout << ans << endl;
}
