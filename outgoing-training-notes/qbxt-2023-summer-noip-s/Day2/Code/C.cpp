#include <bits/stdc++.h>
 
using namespace std;
 
const int kN = 4e5;
int nxt[1 + kN], jump[1 + kN + 1 + 1];
int64_t sum[1 + kN];
 
struct query {
  int l, r, ans;
} q[1 + kN];
 
void testCase() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> sum[i];
    sum[i] += sum[i - 1];
  }
  multiset<int64_t> sums{0};
  int r = 0;
  for (int l = 1; l <= n; ++l) {
    while (r <= n) {
      if (sums.count(sum[r]) >= 2) {
        break;
      }
      r += 1;
      sums.emplace(sum[r]);
    }
    nxt[l] = r + 1;
    sums.erase(sums.find(sum[l - 1]));
  }
  int Q;
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> q[i].l >> q[i].r;
    q[i].ans = 0;
  }
  jump[n + 1] = jump[n + 2] = n + 2;
  for (int j = log2(n); j >= 0; --j) {
    for (int i = 1; i <= n; ++i) {
      jump[i] = nxt[i];
    }
    for (int rep = 1; rep <= j; ++rep) {
      for (int i = 1; i <= n; ++i) {
        jump[i] = jump[jump[i]];
      }
    }
    for (int i = 1; i <= Q; ++i) {
      if (jump[q[i].l] <= q[i].r + 1) {
        q[i].ans += (1 << j);
        q[i].l = jump[q[i].l];
      }
    }
  }
  for (int i = 1; i <= Q; ++i) {
    cout << q[i].ans << '\n';
  }
}
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tests = 1;
  for (int tc = 1; tc <= tests; ++tc) {
    testCase();
  }
  return 0;
}
