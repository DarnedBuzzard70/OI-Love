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

#include <vector>
#include <bitset>
#include <queue>
queue<int> q;
const int N = 50005;
vector<int> vec[N];
bitset<N> dp[N];
int in[N], m, n;
ll ans;
inline void add(int x, int y) { vec[x].push_back(y); ++in[y]; }
#include <assert.h>
int main() {
	read(n), read(m);
	for (int i = 1, x, y; i <= m; ++i)
		read(x), read(y), add(x, y);
	for (int i = 1;i <= n; ++i) {
		dp[i][i] = 1;
		if (!in[i]) q.push(i);
	}
	int cnt = 0;
	while (q.size()) {
		++cnt;
		int x = q.front(); q.pop();
		ans += dp[x].count() - 1;
		for (auto y: vec[x]) {
			dp[y] ^= dp[x];
			if (!--in[y]) q.push(y);
		}
	}
	assert(cnt == n);
	write(ans);
	return 0;
}
