#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b; 
	if(a<b){
		int temp=a;
		a=b;
		b=temp;
	}
	while(b!=0){
		int temp=a%b;
		a=b;
		b=temp;
	}
	cout<<a;
	return 0;
}
