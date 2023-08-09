#include<iostream>
#include<cstdio>
int n, ans, a[110], b[110];
signed main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &b[i]);
	for(int i = 1; i <= n; ++i)
		ans += (a[i] - b[i]) / 10;
	printf("%d\n", ans);
	return 0;
}
