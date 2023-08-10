#include<bits/stdc++.h>
using namespace std;
int main(){
	int b,max=0,flag,temp=0;
	cin>>b;
	int n=b; 
	while(b!=0){
		b--;
		cin>>temp;
		if(temp>max){
			max=temp;
			flag=n-b;
		}
	}
	cout<<flag;
	return 0;
} 
