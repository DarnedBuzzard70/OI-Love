#include <bits/stdc++.h>
using namespace std;
int main(){
	int len=0;
	int temp;
	double sum=0;
	cin>>len;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		sum+=temp;
	}
	double result=sum/len;
	printf("%.2lf",result);
	return 0;
}

