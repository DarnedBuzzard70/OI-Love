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

ll dp[N], ans;
int c[N];

void dfs(int x) {
	ll v1 = 0, v2 = 0;
	for (int i = h[x]; i; i = ne[i]) {
		int y = to[i]; dfs(y);
		ll v = dp[y] + (c[x] ^ c[y]);
		if (v > v1) v2 = v1, v1 = v;
		else if (v > v2) v2 = v;
		dp[x] = max(dp[x], v);
	}
	ans = max(ans, v1 + v2);
}

int main() {
	read(n);
	for (int i = 1;i <= n; ++i) read(c[i]);
	for (int i = 2,f ;i <= n; ++i) 
		read(f), add(f, i);
	dfs(1), write(ans);
	return 0;
}
