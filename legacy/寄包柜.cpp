#include<bits/stdc++.h>
using namespace std;
map <int,map<int,int> > data;
inline int read_int(){
	int ffx250=0;
	char ffxdsb=getchar();
	while(ffxdsb<'0'||ffxdsb>'9'){
		ffxdsb=getchar();
	}
	while(ffxdsb<='9'&& ffxdsb>='0'){
		ffx250=ffx250*10+ffxdsb-48;
		ffxdsb=getchar();
	}
	return ffx250;
}
int main(){
	int n=read_int();
	int q=read_int();
	for(int ffxsb=1;ffxsb<=q;ffxsb+=1){
		int type=read_int();
		int i=read_int(),j=read_int(),k;
		if(type==1){
			k=read_int();
			data[i][j]=k;
		}else{
			printf("%d\n",data[i][j]);
		}
	}
	return 0;
}
