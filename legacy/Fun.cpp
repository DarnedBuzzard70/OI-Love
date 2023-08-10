#include<bits/stdc++.h>
using namespace std;
int t[101];
int q[101];
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
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int main(){
	int n=read_int();
	int m=read_int();
	int type=read_int();
	for(int i=1;i<=n;i++){
		t[i]=read_int();
	}
	for(int i=1;i<=n;i++){
		q[i]=read_int();
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(t[i]==1){
			if(q[i]==1){
				sum+=1;
			}
		}
	}
	int ans=n;
	if(sum>=m){
		ans=ans-(sum-m);
	}
	printf("%d",ans);
	return 0;
}
