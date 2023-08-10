#include<bits/stdc++.h>
using namespace std;
int main(){
	int b;
	cin>>b;
	if(b%4==0&&(b%400==0||b%100!=0)){
		cout<<1;
	}else{
		cout<<0;
	}
	return 0;
}
