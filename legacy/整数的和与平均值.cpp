#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int len;
	cin>>len;
	//scanf("%d" ,&len);
	double temp;
	double sum=0;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		sum+=temp;
	}
	printf("%.0lf %.5lf",sum,sum/len);
	return 0; 
} 
