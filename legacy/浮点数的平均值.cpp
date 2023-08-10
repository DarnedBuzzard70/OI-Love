#include<iostream>
#include<cstdio> 
using namespace std;
int main(){
	int len;
	cin>>len;
	double temp;
	double sum=0;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		sum+=temp;
	}
	printf("%.4lf",sum/len);
	return 0; 
} 
