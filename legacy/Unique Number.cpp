#include<bits/stdc++.h>
using namespace std;
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
int core(int input){
	int ans=0,tmp=10;
	if(input>45){
		return -1;
	}
	for(int i=9;input-i>0;i-=1){
		input-=i;
		tmp=i;
	}
	if(input>0){
		ans+=input;
	}
	for(int i=tmp;i<=9;i++){
		ans*=10;
		ans+=i;
	}
	return ans;
} 
int main(){
	int t=read_int();
	for(int i=1;i<=t;i+=1){
		int x=read_int();
		printf("%d\n",core(x));
	}
	return 0;
} 
