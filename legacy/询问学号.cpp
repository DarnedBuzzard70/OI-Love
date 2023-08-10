#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+10;
int ffx250[MAXN];
inline int read_int(){
	int s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s;
}
int main(){
	int n=read_int();
	int m=read_int();
	for(int i=1;i<=n;i+=1){
		ffx250[i]=read_int();
	}
	for(int i=1;i<=m;i+=1){
		int x=read_int();
		printf("%d\n",ffx250[x]);
	}
	return 0;
}
