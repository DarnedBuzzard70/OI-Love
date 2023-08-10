#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int b;
	int p=1,q=2;
	cin>>b;
	double sum=0;
	for(int i=1;i<=b;i+=1){
		sum+=(double)q/p;
		int a=q;
		q+=p;
		p=a;
	}
	printf("%.4lf",sum);
	return 0;
}
