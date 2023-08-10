#include<bits/stdc++.h>
using namespace std;
const int mod=80112002;
int n,m,ru[5005],chu[5005],a,b,ans,f[5005],mp[5005][5005];
queue<int>q;
inline int ZYC_Fast_Read_int(){
		int s=0,w=1;
		char ch=getchar();
		while(ch<'0'||ch>'9'){
			if(ch=='-')w=-1;
			ch=getchar();
		}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0',ch=getchar();
	}
	return s*w;
}
inline void ZYC_Fast_Write_int(int X) {
	if(X<0) {
		X=~(X-1); putchar('-');
	}
	if(X>9){
		ZYC_Fast_Write_int(X/10);
	}
	putchar(X%10+'0');
}
int main(){
	n=ZYC_Fast_Read_int();
	m=ZYC_Fast_Read_int();
	for(int i=1;i<=m;i++){
		a=ZYC_Fast_Read_int();
		b=ZYC_Fast_Read_int();
		mp[a][b]=1;
		chu[a]++;
		ru[b]++;
	}
	for(int i=1;i<=n;i++){
		if(ru[i]==0) {
			f[i]=1;
			q.push(i);
		}
	}
	while(!q.empty()){
		int a=q.front();
		q.pop();
		for(int k=1;k<=n;k++){
			if(mp[a][k]==0)continue;
			f[k]+=f[a];
			f[k]%=mod;
			ru[k]--;
			if(ru[k]==0){
				if(chu[k]==0){
					ans+=f[k];
					ans%=mod;
                    continue;
				}
				q.push(k);
			}
		}
	} 
	ZYC_Fast_Write_int(ans);
	return 0;
}
