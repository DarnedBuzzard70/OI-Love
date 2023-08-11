#include <bits/stdc++.h>
#define lint long long
using namespace std;
inline int read(){
	char c;int f=1,res=0;
	while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res*f;
}
const int N=505,P=N*N*8;
int hed[P],nxt[P],ver[P],cnt=1;
inline void ae(int u,int v){
	ver[++cnt]=v;
	nxt[cnt]=hed[u];
	hed[u]=cnt;
}
inline void lnk(int u,int v)
	{ae(u,v);ae(v,u);}
vector<int> ex[N][N];
int d[4][2]={{0,1},{1,0},{1,1},{1,-1}};
char c[4]={'-','|','\\','/'};
struct pnt{int x,y,d;}p[P];
int n,m,tot=0;char s[N][N];
inline void inst(int x,int y,int dir){//加点 
	int x0=x+d[dir][0],y0=y+d[dir][1];
	int x1=x-d[dir][0],y1=y-d[dir][1];
	if(x0<1||y0<1||x1<1||y1<1)return;
	if(x0>n||x1>n||y0>m||y1>m)return;
	if(s[x0][y0]=='W'||s[x1][y1]=='W')
		return;
	if(s[x][y]!='W'||s[x0][y0]==s[x1][y1])
		return;
	int u=++tot;p[u]=pnt{x,y,dir};
	for(int v:ex[x][y])lnk(u,v);ex[x][y].push_back(u);
	for(int v:ex[x0][y0])lnk(u,v);ex[x0][y0].push_back(u);
	for(int v:ex[x1][y1])lnk(u,v);ex[x1][y1].push_back(u);
}
inline void build(){//建图 
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<4;++k)
				inst(i,j,k);
}
int ans;
bitset<P> vis,_vis,avis;
inline bool ck(int u){//判断当前点能否选 
	if(_vis[u])return false;
	for(int e=hed[u];e;e=nxt[e])
		if(_vis[ver[e]])return false;
	return true;
}
inline int calc(){//产生初始解 
	int res=0;
	for(int u=1;u<=tot;++u)
		if(ck(u))_vis[u]=1,++res;
	return res;
}
inline int rnd(int md)
	{return 1ll*rand()*rand()%md+1;}
inline int del(int u){
	_vis[u]=0;int res=0;
	for(int e=hed[u];e;e=nxt[e])
		if(ck(ver[e]))_vis[ver[e]]=1,++res;
	return res;
}
inline int upd(){//产生新解 
	_vis=vis;
	int res=0,t=0;
	while(++t<=10){//没什么用的防死循环 
		int u=rnd(tot);
		if(_vis[u])continue;
		_vis[u]=1;++res;
		for(int e=hed[u];e;e=nxt[e]){
			int v=ver[e];
			if(_vis[v])res+=del(v)-1;
			//退掉与u相连的v并更新与v相连的点 
		}break;
	}return res;
}
inline void SA(){
	ans=calc();vis=_vis;
	int res=ans,_res;
	double T=6,dta=0.999995,k=16;
	while(ans<48620){
		_res=res+upd();
		if(_res>=res){
			if(_res>ans)
				ans=_res,avis=_vis,cout<<T<<" "<<_res<<endl;
			vis=_vis;res=_res;
		}else if(exp(k*(_res-res)/T)*2e9>rnd(2e9))
			vis=_vis,res=_res;
		T*=dta;
	}
}
int main(){
	ios::sync_with_stdio(false);
	freopen("05.in","r",stdin);
	n=read();m=read();
	for(int i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	build();SA();
	for(int i=1;i<=tot;++i)
		if(avis[i])
			s[p[i].x][p[i].y]=c[p[i].d];
	freopen("05.ans","w",stdout);
	for(int i=1;i<=n;++i)
		printf("%s\n",s[i]+1);
	return 0;
}