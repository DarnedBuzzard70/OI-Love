#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
template <typename T>
void read(T &x) {
	x = 0; char c = getchar(); int f = 0;
	for (; !isdigit(c); c = getchar())
		f |= c == '-';
	for (; isdigit(c); c = getchar())
		x = x * 10 + (c ^ '0');
	if (f) x = -x;
}

template <typename T>
void write(T x, char ed = '\n') {
	if (x < 0) putchar('-'), x = -x;
	static short st[30], tp;
	do st[++tp] = x % 10, x /= 10; while (x);
	while (tp) putchar(st[tp--] | '0');
	putchar(ed);
}


const int P = 1e9 + 7;
const int N = 100500, M = 105;
int h[N], ne[N], to[N], tot, cnt, m, n;
inline void add(int x, int y) {
	ne[++tot] = h[x], to[h[x] = tot] = y;
}

int dp[N][M];

void dfs(int x, int dep) {
	++cnt;
	for (int i = dep;i <= m; ++i) 
		dp[cnt][i] = (1ll * dp[cnt - 1][i] * (i - dep + 1) + dp[cnt - 1][i - 1]) % P;
	for (int i = h[x]; i; i = ne[i]) dfs(to[i], dep + 1);
}

int main() {
	read(n), read(m), dp[0][0] = 1;
	for (int i = 2, f;i <= n; ++i) read(f), add(f, i);
	dfs(1, 1), write(dp[cnt][m]);
	return 0;
}
