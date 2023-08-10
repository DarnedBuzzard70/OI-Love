#include<bits/stdc++.h>
using namespace std;
inline long long int read_int(){
	long long int s=0;
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
long long int core(long long int a,long long int b,long long int m,long long int n,long long int x,long long int y){
	long long int ax=abs(m-x);
	long long int ay=abs(n-y);
	if(ax%2==1 || ay%2==1 || abs(ax-ay)%4!=0){
		return -1;
	}else{
		long long int ans=max(ax,ay)/2;
		return ans;
	}
}
int main(){
	long long int a=read_int();
	long long int b=read_int();
	long long int m=read_int();
	long long int n=read_int();
	long long int T=read_int();
	for(long long int i=0;i<T;i+=1){
		long long int x=read_int();
		long long int y=read_int();
		printf("%lld\n",core(a,b,m,n,x,y));
	}
	return 0;
} 
