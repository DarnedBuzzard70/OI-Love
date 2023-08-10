#include <bits/stdc++.h>
using namespace std;
int S,T,f[1<<16];
queue<int>q;
int main(){
	for(int i=0,w;i<16;i++){
		scanf("%1d",&w);
		S=S|(w<<i);
	}
	for(int i=0,w;i<16;i++){
		scanf("%1d",&w);
		T=T|(w<<i);
	}
	for(int i=0;i<(1<<16);i++) f[i]=1e9;
	f[S]=0,q.push(S);
	while(q.size()){
		int u=q.front();q.pop();
		for(int i=0;i<15;i++) if((i&3)!=3){
			int tp=(u>>i)&3;
			if(tp==0||tp==3) continue;
			int v=u^(3<<i);
			if(f[v]>f[u]+1) f[v]=f[u]+1,q.push(v);
		}
		for(int i=0;i<12;i++){
			int tp=((u>>i)&1)|(((u>>(i+4))&1)<<1);
			if(tp==0||tp==3) continue;
			int v=u^(1<<i)^(1<<(i+4));
			if(f[v]>f[u]+1) f[v]=f[u]+1,q.push(v);
		}
	}
	printf("%d\n",f[T]);
}
