#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n,m,k,a[300010],L[300010],R[300010],st[300010],t=0,cnt=0;
ll ans=0,len[300010],c[300010];
vector<int>E[300010];
void dfs(int u){
	int son=0;
	for(int v:E[u]){
		dfs(v);
		if(len[v]>len[son]) son=v;
	}
	len[u]=len[son]+a[u];
	for(int v:E[u]) if(son^v) c[cnt++]=len[v];
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),L[i]=i+1,ans+=a[i];
	for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r),L[r]=min(L[r],l);
	for(int i=n;i>=1;i--){
		while(t&&L[i]<=L[st[t]]) t--;
		if(L[i]<=i) st[++t]=i;
		if(t&&L[st[t]]<=i) R[i]=st[t];
		else ans-=a[i],R[i]=i-1;
	}
	st[t=1]=0,R[0]=n;
	for(int i=1;i<=n;i++){
		while(t&&R[st[t]]<i) t--;
		if(R[i]>=i) E[st[t]].push_back(i),st[++t]=i;
	}
	dfs(0),c[cnt++]=len[0];
	if(cnt>=k) nth_element(c,c+cnt-k,c+cnt);
	for(int i=max(cnt-k,0);i<cnt;i++) ans-=c[i];
	printf("%lld\n",ans);
}
