#include <bits/stdc++.h>
using namespace std;
int main(){
	int huaxiao=0;
	int shengyu=0;
	int cunde=0;
	for(int MONTH=1;MONTH<=12;MONTH++){
		cin>>huaxiao;
		shengyu+=300;
		shengyu-=huaxiao;
		if(shengyu<0){
			cout<<"-"<<MONTH;
			return 0;
		}
		for(;shengyu/100!=0;){
			shengyu-=100;
			cunde+=100;
		}
	}
	cout<<shengyu+(int)(1.2*cunde);
	return 0;
}
