#include<bits/stdc++.h>
using namespace std;
int data[10001];
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
int main(){
	int t=read_int();
	for(int i=0;i<t;i++){
		int len=read_int();
		int s=0;
		for(int j=0;j<len;j++){
			int ti=read_int();
			if(ti==0){
				s++;
			}
		}
		printf("%d\n",len-s);
		for(int j=0;j<len;j++){
			printf("1 "); 
		}
		printf("\n");
	}
	return 0;
}
