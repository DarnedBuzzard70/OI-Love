#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int main(){
	double n;
	cin>>n;
	double sum=0;
	for(int i=1;i<=n;i++){
		sum+=pow(-1,i-1)*1/i;
	} 
	printf("%.4lf",sum);
	return 0;
} 
