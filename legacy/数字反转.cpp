#include<bits/stdc++.h>
using namespace std;
int main(){
	int b;
	cin>>b;
	if(b==0){
		cout<<0;
		return 0; 
	}
	if(b<0){
		cout<<"-";
		b*=-1;
	}
	int i=0;
	while(b!=0){
		if(b%10==0){
			if(i==1){
				cout<<b%10;
			}
		}else{
			i=1;
			cout<<b%10;
		}
		b/=10;
	}
	return 0;
}

