#include<iostream>
using namespace std;
int main(){
	int weight;
	char kind;
	cin>>weight>>kind;
	int CNY=0;
	if(kind=='y'){
		CNY+=5;
	}
	if(weight<=1000){
		CNY+=8; 
		cout<<CNY;
		return 0;
	}
	if(weight%500!=0){
		weight+=500;
	}
	CNY+=weight/500*4;		
	cout<<CNY;
	return 0;
} 
