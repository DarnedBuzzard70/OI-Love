#include<iostream>
#include<cmath>
using namespace std;
bool Prime(int n){
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0){
			return false;
		}
	}
	return true;
}
int main(){
	int b;
	cin>>b;
	int time=0;
	for(int i=2;true;i++){
		if(Prime(i)){
			time++;
		}
		if(b==time){
			cout<<i;
			return 0;
		}
	}
	return 0;
} 
