#include <bits/stdc++.h>
#define No() puts("NO"),exit(0)
using namespace std;
int head[300010],o=0,n,m,u[300010],v[300010],ecnt=0;
bool vis[300010],usd[300010];
struct edge{
	int to,link,w;
}e[600010];
void add_edge(int u,int v,int w){
	e[++o]={v,head[u],w},head[u]=o;
	e[++o]={u,head[v],w},head[v]=o;
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].link) if(!usd[e[i].w]) usd[e[i].w]=1,ecnt++;
	for(int i=head[u],v;i;i=e[i].link) if(!vis[v=e[i].to]) dfs(v);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&u[i],&v[i]),add_edge(u[i],v[i],i);
	for(int i=1;i<=n;i++) if(!vis[i]){
		ecnt=0,dfs(i);
		if(ecnt&1) No();
	}
	puts("YES");
}
