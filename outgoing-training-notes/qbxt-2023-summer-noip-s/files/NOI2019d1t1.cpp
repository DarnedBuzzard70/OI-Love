#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
#define ns __gnu_pbds
using namespace std;
const int T=70004,N=150005;
char buf[N+5],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,N,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int x,f=1;for(c=gc;c<'0'||c>'9';c=gc)if(c=='-')f=-f;
	for(x=0;c>='0'&&c<='9';x=x*10+(48^c),c=gc);
	return x*f;
}
struct Dat{int w,lx,rx,ly,ry;}g[N];
vector<int>lk[T];
int n,m,lx[N],rx[N],ly[N],ry[N],mx[N],my[N],lc[N],rc[N],ax[N],ay[N],a[N],lt[N],rt[N];
bool cmptp;
inline bool cmpI(const int &x,const int &y){
	return cmptp?ay[x]<ay[y]:ax[x]<ax[y];
}
typedef long long ll;
typedef pair<ll,int>Tp;
long long d[T],ds[T];
ns::priority_queue<Tp,greater<Tp>,ns::pairing_heap_tag>pq;
double px,py,fx,fy;
bitset<N>vs;
int cnt;
int build(int l,int r){
	int x=l+r>>1,i;ds[x]=1e15;lt[x]=l,rt[x]=r;
	px=py=0;for(i=l;i<=r;++i)px+=ax[a[i]],py+=ay[a[i]];
	fx=fy=0;for(i=l;i<=r;++i)fx+=(px-ax[a[i]])*(px-ax[a[i]]),fy+=(py-ay[a[i]])*(py-ay[a[i]]);
	cmptp=fx<fy,nth_element(a+l,a+x,a+r+1,cmpI);
	lx[x]=rx[x]=mx[x]=ax[a[x]],ly[x]=ry[x]=my[x]=ay[a[x]];
	if(l<x)lc[x]=build(l,x-1),lx[x]=min(lx[x],lx[lc[x]]),rx[x]=max(rx[x],rx[lc[x]]),
	ly[x]=min(ly[x],ly[lc[x]]),ry[x]=max(ry[x],ry[lc[x]]);
	if(x<r)rc[x]=build(x+1,r),lx[x]=min(lx[x],lx[rc[x]]),rx[x]=max(rx[x],rx[rc[x]]),
	ly[x]=min(ly[x],ly[rc[x]]),ry[x]=max(ry[x],ry[rc[x]]);return x;
}
void ask(int l,int r){
	int x=l+r>>1;if(ds[x]<d[0])return;
	if(lx[x]>=g[0].lx&&rx[x]<=g[0].rx&&ly[x]>=g[0].ly&&ry[x]<=g[0].ry){
		ds[x]=d[0];pq.push(Tp(ds[x],x+n));return;
	}if(d[a[x]]>d[0]&&mx[x]>=g[0].lx&&mx[x]<=g[0].rx&&my[x]>=g[0].ly&&my[x]<=g[0].ry)
		d[a[x]]=d[0],pq.push(Tp(d[a[x]],a[x]));
	if(lx[x]>g[0].rx||rx[x]<g[0].lx||ly[x]>g[0].ry||ry[x]<g[0].ly)return;
	if(l<x)ask(l,x-1);if(x<r)ask(x+1,r);return;
}
int main(){
	n=read(),m=read();read(),read();int i,x;
	for(i=1;i<=n;++i)ax[i]=read(),ay[i]=read(),a[i]=i;
	for(i=1;i<=m;++i){
		x=read();g[i]={read(),read(),read(),read(),read()};
		lk[x].push_back(i);
	}build(1,n);
	for(i=2;i<=n;++i)d[i]=1e15;
	pq.push(Tp(d[1],1));
	while(!pq.empty()){
		x=pq.top().second,pq.pop();
		if(vs[x])continue;
		else vs[x]=1;
		if(x>n){
			for(x-=n,i=lt[x];i<=rt[x];++i)
				if(d[a[i]]>ds[x])pq.push(Tp(d[a[i]]=ds[x],a[i]));
		}else{
			for(int y:lk[x])
				g[0]=g[y],d[0]=d[x]+g[y].w,ask(1,n);
		}
	}for(i=2;i<=n;++i)printf("%lld\n",d[i]);
	return 0;
}