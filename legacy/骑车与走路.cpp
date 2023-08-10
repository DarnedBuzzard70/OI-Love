#include<bits/stdc++.h>
using namespace std;
int main(){
	double s;
	cin>>s;
	double ToB=s/3.0+23;
	double ToW=s/1.2;
	if(ToB<ToW){
		cout<<"Bike";
		return 0;
	}
	if(ToB==ToW){
		cout<<"All";
		return 0;
	}
	if(ToB>ToW){
		cout<<"Walk";
		return 0;
	}
}
