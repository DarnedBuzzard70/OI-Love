#include<iostream>
using namespace std;
int main(){
	unsigned long long int data=1;
	int n;
	cin>>n;
	for(int i=0;i<n;i+=1){
		data*=i+1;
	}
	cout<<data;
	return 0;
} 
