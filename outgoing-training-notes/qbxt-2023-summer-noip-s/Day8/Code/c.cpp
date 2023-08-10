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
#include <algorithm>
const int N = 500500;
const int inf = N; 
vector<int> vec[N];
ll dp[N], v[N];
int n, k, mid, tmp;

inline void add(int x, int y) {
	vec[x].push_back(y);
}

void dfs(int x) {
	if (v[x]) tmp -= v[x] >= mid;
	if (vec[x].empty()) return dp[x] = v[x] ? (v[x] >= mid ? 0 : inf) : 1, void();
	for (auto y: vec[x]) dfs(y);
	sort(vec[x].begin(), vec[x].end(), [&](int a, int b) { return dp[a] < dp[b]; });
	int k = vec[x].size() / 2 + 1;
	dp[x] = 0;
	for (int i = 0;i < k; ++i) dp[x] += dp[vec[x][i]];
}

#include <assert.h>
int main() {
	read(n), read(k); assert(n <= 500000);
	for (int i = 2, f;i <= n; ++i) read(f), add(f, i);
	for (int i = n - k + 1;i <= n; ++i) read(v[i]);
	int l = 1, r = k;
	while (l <= r) {
		mid = (l + r) >> 1, tmp = k - mid + 1, dfs(1);
		if (dp[1] > tmp) r = mid - 1;
		else l = mid + 1;
	}
	write(r);
	return 0;
}
