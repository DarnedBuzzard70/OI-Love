#include <bits/stdc++.h>
using namespace std;
int main(){
	int x=0;
	cin>>x;
	if(x<4){
		cout<<0<<endl;
		cout<<0<<endl;
		cout<<0<<endl;
		return 0;
	} 
	if(x%4==0){
		cout<<x/4<<endl;
		cout<<0<<endl;
		cout<<0<<endl;
	}else if(x%4==1){
		cout<<x/4-1<<endl;
		cout<<1<<endl;
		cout<<0<<endl;
	}else if(x%4==2){
		cout<<x/4-1<<endl;
		cout<<0<<endl;
		cout<<1<<endl;
	}else if(x%4==3){
		cout<<x/4-1<<endl;
		cout<<1<<endl;
		cout<<1<<endl;
	} 
	return 0;
}
