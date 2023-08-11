#include<bits/stdc++.h>
#define For(i,x,y) for (register int i=(x);i<=(y);i++)
#define FOR(i,x,y) for (register int i=(x);i<(y);i++)
#define Dow(i,x,y) for (register int i=(x);i>=(y);i--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define fil(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
inline char gc(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar gc
inline ll read(){
    ll x=0,f=1;char c=getchar();
    while ((c<'0'||c>'9')&&(c!='-')) c=getchar();
    if (c=='-') f=-1,c=getchar();
    while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
    return x*f;
}
#undef getchar

const int N = 5e5+10;
int n,a[N];
ll ans[N];
vector<pa>L[N],Q[N];

int top,stk[N],l[N],r[N];
inline void init(){
	For(i,1,n){
		while (top&&a[i]>=a[stk[top]]) --top;
		l[i]=stk[top],stk[++top]=i;
	}
	top=0;
	Dow(i,n,1){
		while (top&&a[i]>a[stk[top]]) --top;
		r[i]=stk[top],stk[++top]=i;
	}
}

struct Seg{
	int lazy[N<<2],mx[N<<2],Mx[N<<2];
	ll ans[N<<2];
	inline void Build(int u,int l,int r){
		lazy[u]=Mx[u]=0;
		if (l==r) return mx[u]=ans[u]=a[l],void(0);
		int mid=l+r>>1;Build(u<<1,l,mid),Build(u<<1^1,mid+1,r);
		mx[u]=ans[u]=max(mx[u<<1],mx[u<<1^1]);
	}
	inline void upd(int u,int x){
		Mx[u]=max(Mx[u],x),lazy[u]=max(lazy[u],x);
		ans[u]=max(ans[u],(ll)mx[u]+Mx[u]);
	}
	inline void push_down(int u){
		if (lazy[u]) upd(u<<1,lazy[u]),upd(u<<1^1,lazy[u]),lazy[u]=0;
	}
	inline void update(int u,int l,int r,int ql,int qr,int x){
		if (ql>qr) return;
		if (l>=ql&&r<=qr) return upd(u,x),void(0);
		int mid=l+r>>1;push_down(u);
		if (qr<=mid) update(u<<1,l,mid,ql,qr,x);
		else if (ql>mid) update(u<<1^1,mid+1,r,ql,qr,x);
		else update(u<<1,l,mid,ql,qr,x),update(u<<1^1,mid+1,r,ql,qr,x);
		ans[u]=max(ans[u<<1],ans[u<<1^1]);
	}
	inline ll Query(int u,int l,int r,int ql,int qr){
		if (l>=ql&&r<=qr) return ans[u];
		int mid=l+r>>1;push_down(u);
		if (qr<=mid) return Query(u<<1,l,mid,ql,qr);
		if (ql>mid) return Query(u<<1^1,mid+1,r,ql,qr);
		return max(Query(u<<1,l,mid,ql,qr),Query(u<<1^1,mid+1,r,ql,qr));
	}
}t;

int main(){
	freopen("three.in","r",stdin);
	freopen("three.out","w",stdout);
	n=read();
	For(i,1,n) a[i]=read();
	int q=read();
	For(i,1,q){
		int l=read(),r=read();
		Q[l].pb(mp(r,i));
	}
	init();
	t.Build(1,1,n);
	For(i,1,n) if (l[i]) L[l[i]].pb(mp(l[i],i));
	Dow(i,n,1){
		for (auto tmp:L[i]) t.update(1,1,n,tmp.se*2-tmp.fi,n,a[tmp.fi]+a[tmp.se]);
		if (r[i]) t.update(1,1,n,r[i]*2-i,n,a[r[i]]+a[i]);
		for (auto j:Q[i]) ans[j.se]=t.Query(1,1,n,i,j.fi);
	}
	For(i,1,q) printf("%lld\n",ans[i]);	
}