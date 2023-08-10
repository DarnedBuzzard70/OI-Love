#include<bits/stdc++.h>
using namespace std;
#define MAXN 6005
int h[MAXN];
int v[MAXN];
vector<int> son[MAXN];
int f[MAXN][2];
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
void dp(int x){
	f[x][0]=0;
	f[x][1]=h[x];
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];
		dp(y);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
	return;
}
int main(){
	int n=read_int();
	for(int i=1;i<=n;i++){
		h[i]=read_int();
	}
	for(int i=1;i<n;i++){
		int x=read_int();
		int y=read_int();
		son[y].push_back(x);
		v[x]=1;
	}
	int start;
	for(int i=1;i<=n;i++){
		if(!v[i]) {
			start=i;
			break;
		}
	}
	dp(start);
	if(f[start][0]>f[start][1]){
		printf("%d",f[start][0]);
	}else{
		printf("%d",f[start][1]);
	}
	return 0;
} 
