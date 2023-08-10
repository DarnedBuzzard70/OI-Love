#include<bits/stdc++.h>
using namespace std;
int data[5001];
int f[5001][5001];
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
int fn(int x,int y){
	if(x==y){
		return data[x]*x;
	}else{
		return min(data[x],data[y])*(x+y);
	}
}
int main(){
	int n=read_int();
	for(int i=1;i<=n;i+=1){
		data[i]=read_int();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j]=fn(i,j);
		}
	}
	int maxn=f[1][1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			maxn=max(f[i][j],maxn);
		}
	}
	printf("%d",maxn);
	return 0;
}
