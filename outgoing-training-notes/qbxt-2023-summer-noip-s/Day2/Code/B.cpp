#include <bits/stdc++.h>
#define int long long
const int mod=998244353;
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e5 + 100;
int n, k, a[maxn], tr[15][maxn], dp[maxn][15];

int lowbit(int x) { return x & (-x); }
void modify(int x, int y, int id) { for (int i = x; i <= n; i += lowbit(i)) (tr[id][i] += y)%=mod; }
int query(int x, int id) { int res = 0; for (int i = x; i; i -= lowbit(i)) (res += tr[id][i])%=mod; return res; }

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();
	for (int i = 1; i <= n; i++) {
		modify(a[i], 1, 1), dp[i][1] = 1;
		for (int j = 2; j <= k + 1; j++) {
			dp[i][j] = query(a[i] - 1, j - 1);
			modify(a[i], dp[i][j], j);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) (ans += dp[i][k + 1])%=mod;
	write(ans);
	return 0;
}
