#include <bits/stdc++.h>

using namespace std;

const int N = 1000005, mod = 998244353;
int n, k, f[N];

int sub(int x, int y) { return x < y ? x + mod - y : x - y; }

int power(int a, int n) {
  int tp = 1;
  while (n) {
    if (n & 1) {
      tp = 1ll * tp * a % mod;
    }
    a = 1ll * a * a % mod, n >>= 1;
  }
  return tp;
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      f[j]++;
    }
  }

  for (int i = 1; i <= n; i++) {
    f[i] = power(f[i], k);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 2 * i; j <= n; j += i) {
      f[j] = sub(f[j], f[i]);
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << f[i] << " \n"[i == n];
  }
}
