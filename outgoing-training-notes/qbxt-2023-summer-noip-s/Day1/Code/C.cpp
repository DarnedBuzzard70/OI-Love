#include<bits/stdc++.h>
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define F(i,l,r) for(int i=l;i<r;++i)
#define pr(...) void(0)//fprintf(stderr,__VA_ARGS__)
const int BUF_SZ=1e6;

char ib[BUF_SZ+1],*ip=ib+BUF_SZ,ob[1<<24],*op=ob;
int read(int L,int R){
	size_t n=ib+BUF_SZ-ip;
	if(n<100){
		memcpy(ib,ip,n);
		fread(ib+n,1,BUF_SZ-n,stdin)[ib+n]=0;
		ip=ib;
	}
	int x=0;
	while(*ip<48)++ip;
	while(*ip>47)x=x*10+*ip++-48;
	assert(L<=x&&x<=R);
	return x;
}
void print(long long x){
	char ss[20];
	int sp=0;
	do ss[sp++]=x%10+48;while(x/=10);
	while(sp)*op++=ss[--sp];
	*op++=10;
}
const int N=1e6+8,sN=1.2e3+8;
typedef unsigned int u32;
typedef unsigned long long u64;
int n,m,B,a[N],ed[N],tk,a0[N];
#define INFO_FMT "%u %u %llu %llu %llu"
#define INFO_(x) (x).e,(x).a,(x).b,(x).c,(x).d
struct Info{
	u32 e,a;
	u64 b,c,d;
	void up(const Info &v){
		pr("up: (" INFO_FMT ") (" INFO_FMT ")\n",INFO_(*this),INFO_(v));
		d+=v.d+v.b*a+c*v.a;
		b+=v.b+(u64)e*v.a;
		c+=v.c+(u64)v.e*a;
		a+=v.a;
		e+=v.e;
		pr("= " INFO_FMT "\n",INFO_(*this));
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

int at(int x){return fill?fill:a[x];}

void cal(int l,int r){
	fill=0;++tk;
	es=0;
	upd(l,r);
	pr("=======\ncal %d,%d\n",l,r);
	Fe(i,l,r)pr("(%d)",at(i));pr("\n");
	Fe(T,1,n){
		if(ed[T]==tk)
		pr("%d: %u %u %llu %llu %llu\n",T,is1[T].e,is1[T].a,is1[T].b,is1[T].c,is1[T].d);
		else pr("%d: ---\n",T);
	}
	F(T,0,m){
		Q &q=qs[T];
		pr("[%d,%d] : %d [%d,%d] %d\n",l,r,q.o,q.l,q.r,q.x);
		if(q.o==2){
			pr("%u %u %llu %llu %llu\n",is2[T].e,is2[T].a,is2[T].b,is2[T].c,is2[T].d);
		}
		if(q.r<l||r<q.l);
		else if(q.l<l){
			if(r<=q.r){
				if(q.o==1){
					ed[fill=q.x]=++tk;
					is1[fill]=Info{0,u32(r-l+1),0,0,0};
					es=0;
				}else{
					pr("[%d %d]\n",a0[T],at(l));
					if(a0[T]!=at(l))is2[T].up1();
					if(ed[q.x]==tk)is2[T].up(is1[q.x]);
					else is2[T].up1(es);
				}
			}else{
				if(q.o==1)modify(l,r,l,q.r,q.x);
				else{
					pr("[%d %d]\n",a0[T],at(l));
					if(a0[T]!=at(l))is2[T].up1();
					is2[T].up(query(l,q.r,q.x));
				}
			}
		}else{
			int R=std::min(r,q.r);
			if(q.o==1)modify(l,r,q.l,R,q.x);
			else is2[T]=query(q.l,R,q.x);
		}
		a0[T]=at(r);
		pr("[%d,%d] : %d [%d,%d] %d end\n",l,r,q.o,q.l,q.r,q.x);
		if(q.o==2){
			pr("%u %u %llu %llu %llu\n",is2[T].e,is2[T].a,is2[T].b,is2[T].c,is2[T].d);
		}else{
			Fe(i,l,r)pr("(%d)",at(i));pr("\n");
			Fe(T,1,n){
				if(ed[T]==tk)
				pr("%d: %u %u %llu %llu %llu\n",T,is1[T].e,is1[T].a,is1[T].b,is1[T].c,is1[T].d);
				else pr("%d: ---\n",T);
			}
		}
	}
}

int main(){
	//freopen( "sample.in" , "r" , stdin );
	//freopen( "sample.out" , "w" , stdout );
	n=read(1,5e5);
	m=read(1,5e5);
	B=sqrt(n);
	Fe(i,1,n)a[i]=read(1,n);
	F(T,0,m){
		int o=read(1,2),l=read(1,n),r=read(l,n),x=read(1,n);
		if(o==1)r=l;
		qs[T]=Q{o,l,r,x};
	}
	for(int l=1,r=B;l<=n;l+=B,r+=B){
		r=std::min(r,n);
		cal(l,r);
	}
	F(T,0,m)if(qs[T].o==2)print(is2[T].d);
	fwrite(ob,1,op-ob,stdout);
	return 0;
}
