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

#include <algorithm>
const int N = 10005001, M = 100050;
int ch[N][2], siz[N], f[N], ed[M], n, tot = 1;
ll v[M];
char s[M];

int insert(char *s) {
	int len = strlen(s + 1), p = 1;
	for (int i = 1;i <= len; ++i) {
		int c = s[i] - '0';
		if (!ch[p][c]) ch[p][c] = ++tot, f[tot] = p;
		p = ch[p][c], ++siz[p];
	}
	return p;
}
#include <assert.h>
int main() {
//	freopen ("13.in","r",stdin); 
	read(n);
	for (int i = 1;i <= n; ++i) {
		scanf ("%s", s + 1), read(v[i]);
		v[i] = v[i] * 2, ed[i] = insert(s);
	}
	for (int i = 1;i <= n; ++i) {
		int p = ed[i];
		while (p) v[i] += siz[p] - 1, p = f[p];
	}
	sort(v + 1, v + n + 1, [&](int x, int y) { return x > y;});
	ll ans = 0;
	for (int i = 1;i <= n; ++i) 
		i & 1 ? ans += v[i] : ans -= v[i];
	write(ans / 2);
	assert(tot < N);
	assert(ans % 2 == 0);
	return 0;
}
