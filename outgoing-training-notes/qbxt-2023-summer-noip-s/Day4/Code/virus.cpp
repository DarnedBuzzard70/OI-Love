#include <bits/stdc++.h>
const int mod=998244353;
using namespace std;
int inv[300010];
void init(int N){
	inv[1]=1;
	for(int i=2;i<=N;i++) inv[i]=mod-1ll*inv[mod%i]*(mod/i)%mod;
}
int main(){
	int n,q,w;
	scanf("%d%d",&n,&q),init(n);
	while(q--){
		scanf("%d",&n);
		int ans=1,mx=0;
		while(n--) scanf("%d",&w),ans=1ll*ans*inv[w]%mod,mx=max(mx,w);
		printf("%d\n",1ll*ans*mx%mod);
	}
}
