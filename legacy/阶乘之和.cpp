#include<bits/stdc++.h>
using namespace std;
int main(){
	int temp=1;
	int sum=0;
	for(int i=1;i<=10;i++){
		temp*=i;
		sum+=temp;
	}
	printf("%d",sum);
	return 0;
}
