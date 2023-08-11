#include<iostream>
#include<cstdio>
#include<map>
#include<algorithm>
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef unsigned long long ll;
const ll B=28,P=1e9+7;
const int N=1000;
int n,a[N],b[N],s[N],su,sx,sy; 
map<ll,ll>h;
bool cmp(int x,int y){return x>y;}
ll dfs(int u,int v){
	ll ret=0;
	if(u==n) return 1;
	if(a[u]+3*(n-v+1)<s[u]) return 0;//保证u打满了总分
	if(v>n){
		FOR(i,u+1,n) b[i]=s[i]-a[i];
		sort(b+u+1,b+n+1);
		ll sta=0;
		FOR(i,u+1,n) sta=sta*B+b[i];//hash
		if(h.find(sta)!=h.end()) return h[sta];
		else return h[sta]=dfs(u+1,u+2);
	}
	if(a[u]+3<=s[u] && sx) 
		a[u]+=3,sx--,ret+=dfs(u,v+1),a[u]-=3,sx++; //u win
	if(a[u]+1<=s[u] && a[v]+1<=s[v] && sy) 
		a[u]++,a[v]++,sy--,ret+=dfs(u,v+1),a[u]--,a[v]--,sy++;//draw
	if(a[v]+3<=s[v] && sx) 
		a[v]+=3,sx--,ret+=dfs(u,v+1),a[v]-=3,sx++;//v win
	return ret%P;
}//一场u-v的比赛 
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&s[i]),su+=s[i];
	sx=su-n*n+n;sy=(su-3*sx)>>1;//算出sx,sy
	sort(s+1,s+n+1,cmp);
	printf("%lld",dfs(1,2)%P);
}
