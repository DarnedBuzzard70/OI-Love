#include <bits/stdc++.h>

using namespace std;

typedef long long i64;

const int N = 305, K = 100005;
int n, m, k;
int st[K], c[K], p[K], top;
int s[N][N];
i64 v[N][K], f[N][N];

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  cin >> n >> m >> k;

  for (int t = 1; t <= n; t++) {
    top = 0;
    st[1] = 0, c[1] = 0;

    for (int i = 1; i <= k; i++) {
      int tp;
      cin >> tp;
      while (top && tp <= c[top]) {
        top--;
      }
      while (top > 1 && p[top - 1] >= (tp - c[top] - 1) / (i - st[top]) + 1) {
        top--;
      }

      top++;
      st[top] = i, c[top] = tp;
      if (top > 1) {
        p[top - 1] = (tp - c[top - 1] - 1) / (i - st[top - 1]) + 1;
      }
    }

    for (int i = 1, j = 1; i <= m; i++) {
      while (j != top && p[j] <= i) {
        j++;
      }
      v[t][i] = 1ll * i * st[j] - c[j];
    }
  }

  while (m--) {
    int l, r;
    cin >> l >> r;
    s[l][r]++;
  }

  for (int i = n; i; i--) {
    for (int j = i; j <= n; j++) {
      s[i][j] += s[i + 1][j];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      s[i][j] += s[i][j - 1];
    }
  }

  for (int i = n; i; i--) {
    for (int j = i; j <= n; j++) {
      for (int k = i; k <= j; k++) {
        f[i][j] = max(f[i][j], f[i][k - 1] + f[k + 1][j] + v[k][s[i][j] - s[i][k - 1] - s[k + 1][j]]);
      }
    }
  }

  cout << f[1][n] << endl;
}
