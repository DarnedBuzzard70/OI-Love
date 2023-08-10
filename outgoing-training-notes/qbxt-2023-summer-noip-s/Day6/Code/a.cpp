#include <bits/stdc++.h>

using namespace std;

const int N = 20000005;
int n, m;
bool np[N], dangerous[N];
int p[N / 5], tot;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  cin >> n >> m;
  while (m--) {
    int p;
    cin >> p;
    dangerous[p] = 1;
  }

  int ans = 0;
  for (int i = 2; i <= n; i++) {
    if (!np[i]) {
      p[++tot] = i;
    }
    if (dangerous[i]) {
      ans++;
    }

    for (int j = 1; j <= tot && i * p[j] <= n; j++) {
      np[i * p[j]] = 1;
      dangerous[i * p[j]] = dangerous[i] | dangerous[p[j]];
      if (i % p[j] == 0) {
        break;
      }
    }
  }

  cout << ans << endl;
}
