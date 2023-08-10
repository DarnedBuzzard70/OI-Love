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

const int N = 1000500;
char s[N];
int f[N], nxt[N], T[31], n;
ll ans;
void KMP() {
	int j = 0;
	for (int i = 2;i <= n; ++i) {
		while (j && f[j + 1] != min(f[i], j + 1)) j = nxt[j];
		if (f[j + 1] == min(f[i], j + 1)) ++j;
		nxt[i] = j, ans += j;
	}
}

int main() {
//	freopen ("13.in","r",stdin);
	scanf ("%s", s + 1), n = strlen(s + 1);
	for (int i = 1;i <= n; ++i) 
		f[i] = i - T[s[i] - 'a'], T[s[i] - 'a'] = i;
	KMP();
	write(ans);
    return 0;
}
