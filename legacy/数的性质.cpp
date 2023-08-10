#include<bits/stdc++.h>
using namespace std;
int main(){
	bool x1,x2;
	int x,s=0;
	cin>>x;
	if(x%2==0){
		x1=true;
		s++;
	}else{
		x1=false;
	}
	if(x>4&&x<=12){
		x2=true;
		s++;
	}else{
		x2=false;
	}
	if(s==2){
		cout<<"1 ";
	}else{
		cout<<"0 ";
	}
	if(s>=1){
		cout<<"1 ";
	}else{
		cout<<"0 ";
	}
	if(s==1){
		cout<<"1 ";
	}else{
		cout<<"0 ";
	}
	if(s==0){
		cout<<"1 ";
	}else{
		cout<<"0 ";
	}
	return 0;
}
