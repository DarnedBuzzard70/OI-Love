#include<stdio.h>
#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<=r;++i)
const int N=1e6+7;
int _(){
	int x=0,c=getchar();
	while(c<48)c=getchar();
	while(c>47)x=x*10+c-48,c=getchar();
	return x;
}
int n,m,t,la;
int fa[N],in[N],q[N],ql=0,qr=0,c[N],c0[N],ws[N],e0[N],nx[N];
int sz[N],son[N],top[N],len[N],id[N],idp=0,ss[N];
void ins(int i){
	int w=ws[i],z=top[w],d=t+id[w]-id[z];
	++c[c0[i]=id[z]+d%len[z]];
	if(!in[z]&&++d<=m)ws[i]=fa[z],nx[i]=e0[d],e0[d]=i;
}
int que(int w){
	int z=top[w];
	return c[id[z]+(t+id[w]-id[z])%len[z]];
}
int main(){
	n=_();
	assert(1<=n&&n<=500000);
	F(i,1,n)++in[fa[i]=_()],assert(1<=fa[i]&&fa[i]<=n);
	F(i,1,n)if(!in[i])sz[q[++qr]=i]=1;
	while(ql!=qr){
		int w=q[++ql],f=fa[w];
		sz[f]+=sz[w];
		if(sz[w]>sz[son[f]])son[f]=w;
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
	for(m=_(),t=1,assert(1<=m&&m<=500000);t<=m;++t){
		for(int i=e0[t],j;i;j=nx[i],--c[c0[i]],ins(i),i=j);
		int w=ws[t]=_()^la;
		assert(1<=w&&w<=n);
		ins(t);
		printf("%d\n",la=que(w));
//		la=0;
	}
	return 0;
}
