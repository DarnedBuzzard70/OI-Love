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

#include <assert.h>
const int N = 1010500;
ll n, k, m, l[N], r[N], c[N];
char s[N];

int main() {
	read(n), read(m), read(k);
	scanf ("%s", s + 1);
	assert(k);
	for (int i = 1;i <= m; ++i) {
		read(l[i]), read(r[i]), read(c[i]);
		assert(l[i]);
	}
	for (int i = m;i >= 1; --i) {
		int len = r[i] - l[i] + 1, L = c[i] + 1, R = c[i] + len;
		if (L <= k && k <= R) k += l[i] - L;
		else if (k > R) k -= len;
	}
	write(k);
	putchar(s[(k - 1) % n + 1]);
	return 0;
}

/*

*/
