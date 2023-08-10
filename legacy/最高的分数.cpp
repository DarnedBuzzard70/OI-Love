#include<iostream>
#include<cstdio> 
using namespace std;
int main(){
	int len;
	int max=0;
	cin>>len;
	int temp;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		if(max<temp){
			max=temp;
		} 
	}
	cout<<max;
	return 0; 
} 
