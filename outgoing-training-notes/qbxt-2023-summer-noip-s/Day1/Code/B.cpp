#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
	
const int MEM=1<<26;
char pool[MEM],*pool_p=pool;

template<class T>
void alloc(T *&p,int sz){
	p=new T[sz];
}
	
template<class D,class M>
struct MSegTree{
	struct Node{
		D d;
		M m;
		void app(const M &t){
			d*=t;
			m*=t;
		}
		void up(const Node &a,const Node &b){
			d=a.d+b.d;
			d*=m;
		}
	}*tr;
	int mx;
	int n;
	void in(int x){assert(1<=x&&x<=n);}
	void in(int l,int r){assert(1<=l&&l<=r&&r<=n);}
	void alloc(int n){
		for(mx=1;mx<n+2;mx<<=1);
		::alloc(tr,mx+n+3);
		this->n=n;
	}
	template<class T>
	void init(int n,T *d0){
		alloc(n);
		Fe(i,1,n)tr[mx+i].d=d0[i];
		range_update(1,n);
	}
	void range_update(int l,int r){
		in(l),in(r);
		l+=mx,r+=mx;
		for(l>>=1,r>>=1;l<r;l>>=1,r>>=1){
			Fe(x,l,r)up(x);
		}
		for(;l;l>>=1)up(l);
	}
	void up(int x){
		tr[x].up(tr[x*2],tr[x*2+1]);
	}
	void update(int l,int r,const M &t){
		in(l),in(r);
		for(l+=mx-1,r+=mx+1;l^r^1;up(l>>=1),up(r>>=1)){
			if(~l&1)tr[l+1].app(t);
			if(r&1)tr[r-1].app(t);
		}
		for(;l>1;up(l>>=1));
	}
	D query(int l,int r){
		in(l),in(r);
		D a1,a2;
		for(l+=mx-1,r+=mx+1;l^r^1;a1*=tr[l>>=1].m,a2*=tr[r>>=1].m){
			if(~l&1)a1=a1+tr[l+1].d;
			if(r&1)a2=tr[r-1].d+a2;
		}
		a1=a1+a2;
		for(;l>1;a1*=tr[l>>=1].m);
		return a1;
	}
};

typedef long long i64;
int read(int L,int R){
	int x;
	assert(scanf("%d",&x)==1);
	assert(L<=x&&x<=R);
	return x;
}

struct M{
	i64 a;
	M(i64 x=0):a(x){}
	void operator*=(const M &m){
		a+=m.a;
	}
};

const i64 inf=1LL<<60;
using std::max;

struct D{
	i64 s2,s3;
	i64 l1,l2,r1,r2;
	int n;
	D():s2(-inf),s3(-inf),l1(-inf),l2(-inf),r1(-inf),r2(-inf),n(0){}
	D(i64 x):s2(-inf),s3(-inf),l1(x),l2(-inf),r1(x),r2(-inf),n(1){}
	D(const D &a,const D &b){
		s2=max(max(a.s2,b.s2),a.r1+b.l1);
		s3=max(max(a.s3,b.s3),max(a.r1+b.l2,a.r2+b.l1));
		l1=a.l1;
		l2=a.l2;
		r1=b.r1;
		r2=b.r2;
		n=a.n+b.n;
		if(a.n==1)l2=max(l2,a.l1+b.l1);
		if(b.n==1)r2=max(r2,a.r1+b.r1);
	}
	void operator*=(const M &m){
		s2+=m.a*2;
		s3+=m.a*3;
		l1+=m.a;
		l2+=m.a*2;
		r1+=m.a;
		r2+=m.a*2;
	}
	friend D operator+(const D &a,const D &b){
		return D(a,b);
	}
};

const int maxn=1e6,maxm=1e6,maxv=1e3,N=maxm+10;
i64 a[N];
int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	MSegTree<D,M> tr;
	Fe(i,1,n)a[i]=read(-maxv,maxv);
	tr.init(n,a);
	Fe(_,1,m){
		int o=read(1,2);
		int l=read(1,n);
		if(o==1){
			int r=read(l,n);
			int x=read(-maxv,maxv);
			tr.update(l,r,M(x));
		}else{
			int r=read(l+1,n);
			D ans=tr.query(l,r);
			i64 a,b;
			if(ans.s2*3>ans.s3*2){
				a=ans.s2;
				b=2;
			}else{
				a=ans.s3;
				b=3;
			}
			if(a%b==0)a/=b,b=1;
			printf("%lld/%lld\n",a,b);
		}
	}
	return 0;
}
