#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <cstring>
#define ll unsigned long long
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

const int P = 1e9 + 9;
const int N = 10050000;
int e[N], pr[N], a[N], num, v[N], n, k;
ll mi[N/10];
int m1[N/10];
void work(int n = 1e7) {
	mi[0] = m1[0] = 1;
	for (int i = 2;i <= n; ++i) {
		if (!e[i]) pr[e[i] = ++num] = i;
		for (int j = 1;j <= e[i] && pr[j] * i <= n; ++j)
			e[pr[j] * i] = j;
	}
	for (int i = 1;i <= num; ++i) {
		mi[i] = mi[i - 1] * 27ull;
		m1[i] = m1[i - 1] * 137ll % P;
	}
}

#include <map> 
map<pair<ll, int> , int> mp;
#include <assert.h>
int main() {
//	freopen ("11.in","r",stdin);
	read(n), read(k), work();
	ll all = 0, ans = 0;
	long long a2 = 0;
	mp[{all, a2}] = 1;
	for (int i = 1, x;i <= n; ++i) {
		read(x); 
		while (x != 1) {
			int t = e[x];
			all = (all + mi[t]);
			a2 = (a2 + m1[t]) % P;
			if (++v[t] == k) {
				v[t] = 0, all = (all - mi[t] * k);
				a2 = (a2 - 1ll * m1[t] * k % P + P) % P;
			}
			x /= pr[t];
		}
		ans += mp[{all, a2}]++;
	}
	write(ans);
	return 0;
}
