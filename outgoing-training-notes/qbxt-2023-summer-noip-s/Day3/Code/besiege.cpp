#include <bits/stdc++.h>
#define No() puts("NO"),exit(0)
typedef long long ll;
using namespace std;
int n,m,head[300010],o=0;
ll dis[300010];
struct edge{
	int link,to,w;
}e[600010];
struct nd{
	int id;
	ll w;
	bool operator <(const nd &b)const{
		return w>b.w;
	}
};
void add_edge(int u,int v,int w){
	e[++o]={head[u],v,w},head[u]=o;
	e[++o]={head[v],u,w},head[v]=o;
}
priority_queue<nd>q;
void dijk(){
	for(int i=1;i<=n;i++) dis[i]=1e18;
	q.push({1,dis[1]=0});
	while(q.size()){
		int u=q.top().id;
		if(q.top().w^dis[u]){q.pop();continue;}
		q.pop();
		for(int i=head[u],v;i;i=e[i].link) if(dis[v=e[i].to]>dis[u]+e[i].w){
			q.push({v,dis[v]=dis[u]+e[i].w});
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++) scanf("%d%d%d",&u,&v,&w),add_edge(u,v,w);
	dijk();
	for(int u=2;u<=n;u++){
		int c=0;
		for(int i=head[u],v;i;i=e[i].link) if(dis[v=e[i].to]+e[i].w==dis[u]){
			c++;
			if(v==1) c++;
		}
		if(c<2) No();
	}
	puts("YES");
}
