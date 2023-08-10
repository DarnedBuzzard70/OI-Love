#include<bits/stdc++.h>
using namespace std;
bool NRwS(int b){
	if(b%7==0){
		return true;
	}
	while(b!=0){
		if(b%10==7){
			return true;
		}
		b/=10;
	}
	return false; 
} 
int main(){
	int b;
	cin>>b;
	int sum=0;
	for(int i=1;i<=b;i++){
		if(!NRwS(i)){
			sum+=pow(i,2);
		}
	}
	cout<<sum;
	return 0;
}
