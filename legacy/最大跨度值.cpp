#include<iostream>
#include<cstdio> 
using namespace std;
int main(){
	int len;
	int max=0;
	int min=1000;
	cin>>len;
	int temp;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		if(max<temp){
			max=temp;
		}
		if(min>temp){
			min=temp;
		}
	}
	cout<<max-min;
	return 0; 
} 
