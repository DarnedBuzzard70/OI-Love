### 清北学堂 Day 1 总结

------------


## 背景
```
二中信竞_姜Sir 202385 175823
需要孩子们把此次济南清北学堂刷题营的比赛题目，赛后全部订正完。

二中信竞_姜Sir 202385 175835
相当于赛后复盘，要求每一场的比赛题目基本全部订正完成后(能力所及)，重写赛后总结，命好名，发在本群，我检查，希望家长们能督促孩子们完成

二中信竞_姜Sir 202385 175853
以上复盘任务，从今天开始，截止到8月15日，要求全部完成

二中信竞_姜Sir 202385 175902
家长的督促和监督，很重要


```

于是就有了下面这些。

## 材料准备

- 题目链接：[LINK](httpsnoip.acrsproblemsetshow239)

## 题解 & 思路

### T1

- 题目内容

	大嘴乌鸦有 $n$ 个水瓶，第 $i$ 个水瓶重量为 $a_i$。

	乌鸦要喝水，所以他找来了一堆石子，这些石子的重量的和为 $k$。

	乌鸦发现，如果一个区间的水瓶的重量的异或和是他找的所有石子重量和的因子，则这个区间是一个合法的喝水区间。

	乌鸦想知道，有多少个不同的喝水区间。

- 题意简化

	求有多少个区间异或和为 $k$ 的因子。

- 真 • 题意简化

	$k$ 的因子数量小于等于 $2 sqrt k$，问题可以简化成求有多少个区间异或和为 $x$。
  
	显然：异或满足差分性质。记异或前缀和为 $pre_x$ （规定 $pre_0=0$），有 $a_loplus a_{l+1}oplus a_{l+2}oplus ...oplus a_r = pre_roplus pre_{l-1}$。
   
   问题转化为对于任意的 $r$ 有多少个 $l$ 满足 $pre_{l-1}=pre_roplus k$，使用桶来维护。

### T2

- 题意简化

	给定一个长度 $n$ 的序列 $a_1,dots,a_n$，共 $m$ 次操作，共两种操作类型：

	1. 给定 $l,r,x$，将 $a_l,dots,a_r$ 加上 $x$。
	2. 给定 $l,r$，查询 $mathop{max}limits_{lle LRle r}frac{sumlimits_{i=L}^R a_i}{R-L+1}$ 。
    
- 思路分析

	考虑对于任意区间长度 $≥4$ 的区间，其可以被划分为两个长度 $≥2$ 的区间，而这两个区间的平均值一定有一个不必原区间小，故答案区间长度 $≤3$ 。然后用线段树维护每个长度为 $2$ 的区间和长度为 $3$ 的区间的最大值即可。
    
### T3 & T4

由于难度问题和考试范围，就先不写了，有时间再写。

## 标程 

这里是老师提供的 std 程序。

### T1

```cpp
#include iostream
#include stdio.h
#define MAXN 100010

using namespace std;

int n , k , a[ MAXN ] , cnt[ MAXN  4 ] , v[ MAXN ] , tot;
long long ans = 0;

int main()
{
	freopen( data9.in , r , stdin );
	freopen( data9.out , w , stdout );
	cin  n  k;
	for( int i = 1 ; i = k ; i++ )
		if( k % i == 0 )
			v[ ++tot ] = i;
	for( int i = 1 ; i = n ; i++ )
	{
		cin  a[i];
		a[i] ^= a[i - 1];
	}
	cnt[0]++;
	for( int i = 1 ; i = n ; i++ )
	{
		for( int j = 1 ; j = tot ; j++ )
			ans += cnt[ a[i] ^ v[j] ];
		cnt[ a[i] ]++;
	}
	cout  ans  endl;
	return 0;
}

```

### T2

```cpp
#includebitsstdc++.h
#define F(i,l,r) for(int i=l;ir;++i)
#define Fe(i,l,r) for(int i=l;i=r;++i)
#define Fer(i,l,r) for(int i=l;i=r;--i)
	
const int MEM=126;
char pool[MEM],pool_p=pool;

templateclass T
void alloc(T &p,int sz){
	p=new T[sz];
}
	
templateclass D,class M
struct MSegTree{
	struct Node{
		D d;
		M m;
		void app(const M &t){
			d=t;
			m=t;
		}
		void up(const Node &a,const Node &b){
			d=a.d+b.d;
			d=m;
		}
	}tr;
	int mx;
	int n;
	void in(int x){assert(1=x&&x=n);}
	void in(int l,int r){assert(1=l&&l=r&&r=n);}
	void alloc(int n){
		for(mx=1;mxn+2;mx=1);
		alloc(tr,mx+n+3);
		this-n=n;
	}
	templateclass T
	void init(int n,T d0){
		alloc(n);
		Fe(i,1,n)tr[mx+i].d=d0[i];
		range_update(1,n);
	}
	void range_update(int l,int r){
		in(l),in(r);
		l+=mx,r+=mx;
		for(l=1,r=1;lr;l=1,r=1){
			Fe(x,l,r)up(x);
		}
		for(;l;l=1)up(l);
	}
	void up(int x){
		tr[x].up(tr[x2],tr[x2+1]);
	}
	void update(int l,int r,const M &t){
		in(l),in(r);
		for(l+=mx-1,r+=mx+1;l^r^1;up(l=1),up(r=1)){
			if(~l&1)tr[l+1].app(t);
			if(r&1)tr[r-1].app(t);
		}
		for(;l1;up(l=1));
	}
	D query(int l,int r){
		in(l),in(r);
		D a1,a2;
		for(l+=mx-1,r+=mx+1;l^r^1;a1=tr[l=1].m,a2=tr[r=1].m){
			if(~l&1)a1=a1+tr[l+1].d;
			if(r&1)a2=tr[r-1].d+a2;
		}
		a1=a1+a2;
		for(;l1;a1=tr[l=1].m);
		return a1;
	}
};

typedef long long i64;
int read(int L,int R){
	int x;
	assert(scanf(%d,&x)==1);
	assert(L=x&&x=R);
	return x;
}

struct M{
	i64 a;
	M(i64 x=0)a(x){}
	void operator=(const M &m){
		a+=m.a;
	}
};

const i64 inf=1LL60;
using stdmax;

struct D{
	i64 s2,s3;
	i64 l1,l2,r1,r2;
	int n;
	D()s2(-inf),s3(-inf),l1(-inf),l2(-inf),r1(-inf),r2(-inf),n(0){}
	D(i64 x)s2(-inf),s3(-inf),l1(x),l2(-inf),r1(x),r2(-inf),n(1){}
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
	void operator=(const M &m){
		s2+=m.a2;
		s3+=m.a3;
		l1+=m.a;
		l2+=m.a2;
		r1+=m.a;
		r2+=m.a2;
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
	MSegTreeD,M tr;
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
			if(ans.s23ans.s32){
				a=ans.s2;
				b=2;
			}else{
				a=ans.s3;
				b=3;
			}
			if(a%b==0)a=b,b=1;
			printf(%lld%lldn,a,b);
		}
	}
	return 0;
}

```

### T3
```cpp
#includebitsstdc++.h
#define Fe(i,l,r) for(int i=l;i=r;++i)
#define F(i,l,r) for(int i=l;ir;++i)
#define pr(...) void(0)fprintf(stderr,__VA_ARGS__)
const int BUF_SZ=1e6;

char ib[BUF_SZ+1],ip=ib+BUF_SZ,ob[124],op=ob;
int read(int L,int R){
	size_t n=ib+BUF_SZ-ip;
	if(n100){
		memcpy(ib,ip,n);
		fread(ib+n,1,BUF_SZ-n,stdin)[ib+n]=0;
		ip=ib;
	}
	int x=0;
	while(ip48)++ip;
	while(ip47)x=x10+ip++-48;
	assert(L=x&&x=R);
	return x;
}
void print(long long x){
	char ss[20];
	int sp=0;
	do ss[sp++]=x%10+48;while(x=10);
	while(sp)op++=ss[--sp];
	op++=10;
}
const int N=1e6+8,sN=1.2e3+8;
typedef unsigned int u32;
typedef unsigned long long u64;
int n,m,B,a[N],ed[N],tk,a0[N];
#define INFO_FMT %u %u %llu %llu %llu
#define INFO_(x) (x).e,(x).a,(x).b,(x).c,(x).d
struct Info{
	u32 e,a;
	u64 b,c,d;
	void up(const Info &v){
		pr(up ( INFO_FMT ) ( INFO_FMT )n,INFO_(this),INFO_(v));
		d+=v.d+v.ba+cv.a;
		b+=v.b+(u64)ev.a;
		c+=v.c+(u64)v.ea;
		a+=v.a;
		e+=v.e;
		pr(=  INFO_FMT n,INFO_(this));
	}
	void up1(u32 x=1){
		up(Info{x,0,0,0,0});
	}
	void up2(u32 x=1){
		up(Info{0,x,0,0,0});
	}
	void upe(u32 e0){
		if(e!=e0)up1(e0-e);
	}
}is1[N],is2[N];

struct Q{
	int o,l,r,x;
}qs[N];

int fill=0;
u32 es=0;

void upd(int l,int r){
	Fe(i,l,r)is1[a[i]]=Info{0,0,0,0,0};
	u32 e=0;
	int x1=a[l];
	Fe(i,l,r){
		int x2=a[i];
		if(x2!=x1)++e;
		is1[x2].upe(e);
		is1[x2].up2();
		x1=x2;
	}
	++tk;
	Fe(i,l,r)is1[a[i]].upe(e),ed[a[i]]=tk;
	es=e;
}

void modify(int l,int r,int L,int R,int x){
	if(fill){
		Fe(i,l,r)a[i]=fill;
		fill=0;++tk;
	}
	Fe(i,L,R)a[i]=x;
	upd(l,r);
}

Info query(int l,int r,int x){
	if(fill){
		if(fill==x)return Info{0,u32(r-l+1),0,0,0};
		return Info{0,0,0,0,0};
	}
	int x1=a[l];
	Info v{0,x1==x,0,0,0};
	Fe(i,l+1,r){
		int x2=a[i];
		if(x2!=x1)v.up1();
		if(x2==x)v.up2();
		x1=x2;
	}
	return v;
}

int at(int x){return fillfilla[x];}

void cal(int l,int r){
	fill=0;++tk;
	es=0;
	upd(l,r);
	pr(=======ncal %d,%dn,l,r);
	Fe(i,l,r)pr((%d),at(i));pr(n);
	Fe(T,1,n){
		if(ed[T]==tk)
		pr(%d %u %u %llu %llu %llun,T,is1[T].e,is1[T].a,is1[T].b,is1[T].c,is1[T].d);
		else pr(%d ---n,T);
	}
	F(T,0,m){
		Q &q=qs[T];
		pr([%d,%d]  %d [%d,%d] %dn,l,r,q.o,q.l,q.r,q.x);
		if(q.o==2){
			pr(%u %u %llu %llu %llun,is2[T].e,is2[T].a,is2[T].b,is2[T].c,is2[T].d);
		}
		if(q.rlrq.l);
		else if(q.ll){
			if(r=q.r){
				if(q.o==1){
					ed[fill=q.x]=++tk;
					is1[fill]=Info{0,u32(r-l+1),0,0,0};
					es=0;
				}else{
					pr([%d %d]n,a0[T],at(l));
					if(a0[T]!=at(l))is2[T].up1();
					if(ed[q.x]==tk)is2[T].up(is1[q.x]);
					else is2[T].up1(es);
				}
			}else{
				if(q.o==1)modify(l,r,l,q.r,q.x);
				else{
					pr([%d %d]n,a0[T],at(l));
					if(a0[T]!=at(l))is2[T].up1();
					is2[T].up(query(l,q.r,q.x));
				}
			}
		}else{
			int R=stdmin(r,q.r);
			if(q.o==1)modify(l,r,q.l,R,q.x);
			else is2[T]=query(q.l,R,q.x);
		}
		a0[T]=at(r);
		pr([%d,%d]  %d [%d,%d] %d endn,l,r,q.o,q.l,q.r,q.x);
		if(q.o==2){
			pr(%u %u %llu %llu %llun,is2[T].e,is2[T].a,is2[T].b,is2[T].c,is2[T].d);
		}else{
			Fe(i,l,r)pr((%d),at(i));pr(n);
			Fe(T,1,n){
				if(ed[T]==tk)
				pr(%d %u %u %llu %llu %llun,T,is1[T].e,is1[T].a,is1[T].b,is1[T].c,is1[T].d);
				else pr(%d ---n,T);
			}
		}
	}
}

int main(){
	freopen( sample.in , r , stdin );
	freopen( sample.out , w , stdout );
	n=read(1,5e5);
	m=read(1,5e5);
	B=sqrt(n);
	Fe(i,1,n)a[i]=read(1,n);
	F(T,0,m){
		int o=read(1,2),l=read(1,n),r=read(l,n),x=read(1,n);
		if(o==1)r=l;
		qs[T]=Q{o,l,r,x};
	}
	for(int l=1,r=B;l=n;l+=B,r+=B){
		r=stdmin(r,n);
		cal(l,r);
	}
	F(T,0,m)if(qs[T].o==2)print(is2[T].d);
	fwrite(ob,1,op-ob,stdout);
	return 0;
}

```

### T4

```cpp
#includestdio.h
#includebitsstdc++.h
#define F(i,l,r) for(int i=l;i=r;++i)
const int N=1e6+7;
int _(){
	int x=0,c=getchar();
	while(c48)c=getchar();
	while(c47)x=x10+c-48,c=getchar();
	return x;
}
int n,m,t,la;
int fa[N],in[N],q[N],ql=0,qr=0,c[N],c0[N],ws[N],e0[N],nx[N];
int sz[N],son[N],top[N],len[N],id[N],idp=0,ss[N];
void ins(int i){
	int w=ws[i],z=top[w],d=t+id[w]-id[z];
	++c[c0[i]=id[z]+d%len[z]];
	if(!in[z]&&++d=m)ws[i]=fa[z],nx[i]=e0[d],e0[d]=i;
}
int que(int w){
	int z=top[w];
	return c[id[z]+(t+id[w]-id[z])%len[z]];
}
int main(){
	n=_();
	assert(1=n&&n=500000);
	F(i,1,n)++in[fa[i]=_()],assert(1=fa[i]&&fa[i]=n);
	F(i,1,n)if(!in[i])sz[q[++qr]=i]=1;
	while(ql!=qr){
		int w=q[++ql],f=fa[w];
		sz[f]+=sz[w];
		if(sz[w]sz[son[f]])son[f]=w;
		if(!--in[f])q[++qr]=f;
	}
	for(int i=qr,w;i;--i)if(!top[w=q[i]]){
		for(int u=w;u;u=son[u])top[u]=w,id[u]=++idp;
		len[w]=idp-id[w]+1;
	}
	F(w,1,n)if(in[w]==1){
		int sp=0;
		for(int u=fa[w];in[u]==1;in[u]=2,u=fa[u])top[u]=w,ss[++sp]=u;
		for(len[w]=sp;sp;id[ss[sp--]]=++idp);
	}
	for(m=_(),t=1,assert(1=m&&m=500000);t=m;++t){
		for(int i=e0[t],j;i;j=nx[i],--c[c0[i]],ins(i),i=j);
		int w=ws[t]=_()^la;
		assert(1=w&&w=n);
		ins(t);
		printf(%dn,la=que(w));
		la=0;
	}
	return 0;
}

```
