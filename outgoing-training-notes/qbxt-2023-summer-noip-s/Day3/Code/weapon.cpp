#include <bits/stdc++.h>
using namespace std;
int read(){
	int t=0;
	static char ch;
	while(ch=getchar(),ch<'0'||ch>'9');
	t=ch^48;
	while(ch=getchar(),ch>='0'&&ch<='9') t=t*10+(ch^48);
	return t; 
}
int n,m,ans,k,pv[510],qv[510],pre[510];
int vis[510];
struct nd{
	int l,r,w;
}c[1000010];
void build(){
	queue<int>q;
	for(int i=0;i<m;i++) vis[i]=0,pre[i]=-1;
	for(int i=0;i<m;i++) if(!~pv[i]) q.push(i),vis[i]=1;
	while(q.size()){
		int u=q.front();q.pop();
		for(int j=0;j<k;j++) if(c[j].l<=u&&c[j].r>=u&&!vis[qv[j]]){
			q.push(qv[j]),vis[qv[j]]=1,pre[qv[j]]=u;
		}
	}
	for(int i=1;i<m;i++) vis[i]+=vis[i-1];
}
void work(int l,int r,int w){
	int tp=vis[r]-(l?vis[l-1]:0);
	if(!tp) return;
	c[k++]={l,r,w},ans+=w;
	int u=0,v=k-1;
	for(int i=l;i<=r;i++) if(vis[i]-(i?vis[i-1]:0)){
		u=i;
		break;
	}
	do{
		int tp=pv[u];
		pv[u]=v,qv[v]=u,u=pre[u],v=tp;
	}while(~v);
	build();
}
int main(){
	m=read(),n=read();
	for(int i=0;i<n;i++) c[i].l=read(),c[i].r=read(),c[i].w=read(),c[i].l--,c[i].r--;
	sort(c,c+n,[](nd a,nd b){return a.w>b.w;});
	for(int i=0;i<m;i++) pv[i]=qv[i]=-1;
	ans=k=0;
	build();
	for(int i=0;i<n;i++) work(c[i].l,c[i].r,c[i].w);
	printf("%d %d\n",k,ans);
}
