#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n,m,u[300010],v[300010],a[300010],b[300010],fa[300010];
struct ed{
	int u,v;
	ll w;
}e[300010];
ll x;
int find(int a){
	return fa[a]==a?a:fa[a]=find(fa[a]);
}
bool mge(int u,int v){
	return u=find(u),v=find(v),fa[u]=v,u!=v;
}
bool chk(ll mid){
	for(int i=1;i<=m;i++) e[i].u=u[i],e[i].v=v[i],e[i].w=a[i]+mid*b[i];
	sort(e+1,e+m+1,[](ed p,ed q){return p.w<q.w;});
	iota(fa,fa+n+1,0);
	ll tp=x;
	for(int i=1;i<=m;i++) if(mge(e[i].u,e[i].v)){
		tp-=e[i].w;
		if(tp<0) return 1;
	}
	return 0;
}
int main(){
	scanf("%d%d%lld",&n,&m,&x);
	for(int i=1;i<=m;i++) scanf("%d%d%d%d",&u[i],&v[i],&a[i],&b[i]);
	ll l=0,r=x,ans=x;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(chk(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%lld\n",ans);
}
