#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int b=1;
	int sum=0;
	while(sum<=1000){
		sum+=b++;
	}
	cout<<b-1;
	return 0;
}
