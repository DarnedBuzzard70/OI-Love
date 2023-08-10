#include<bits/stdc++.h>
using namespace std;
int mp[111][22222];
inline int read_int(){
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			w=-1;
		} 
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';ch=getchar();
	}
	return s*w;
}
int mod(int data){
	return data%504;
}
int dfs(int n,int k){
	if(mp[n][k]!=-1){
		return mp[n][k];
	}
	if((n==1&&k==0) || (n==1&&k==1)){
		return 1;
	}
	if(n==1){
		return 0;
	}
	mp[n][k]=mod(dfs(n-1,k)+dfs(n-1,k-1)*(4*n-2*k-2)+dfs(n-1,k-2)*(2*n-k-1)*(2*n-k));
	return mp[n][k];
}
int main(){
	memset(mp,0xff,sizeof(mp));
	int n,k;
	n=read_int();
	k=read_int();
	if(k>2*n-1){
		puts("0");
		return 0;
	}
	printf("%d\n",dfs(n,k));
	return 0;
} 
