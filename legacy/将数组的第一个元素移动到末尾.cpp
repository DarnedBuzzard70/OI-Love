#include<bits/stdc++.h>
using namespace std;
int a[10];
int main(){
	for(int i=0;i<10;i++){
		cin>>a[i];
	}
	for(int i=1;i<11;i++){
		cout<<a[i%10]<<" ";
	}
	return 0;
}
