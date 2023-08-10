#include<bits/stdc++.h>
using namespace std;
void fn(){
	int a;
	if(cin>>a){
		fn();
	}else{
		return;
	}
	cout<<a<<" ";
}
int main(){
	fn();
	return 0;
}
