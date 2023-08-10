#include <bits/stdc++.h>
const int mod=998244353;
using namespace std;
int n,sz[300010],ans=0;
vector<int>E[300010];
void dfs(int u){
	sz[u]=1;
	for(int v:E[u]){
		dfs(v);
		sz[u]+=sz[v];
	}
	if(2*(sz[u]-1)>=n) ans++;
}
int main(){
	scanf("%d",&n);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),E[fa].push_back(i);
	dfs(1);
	printf("%d\n",ans);
}
