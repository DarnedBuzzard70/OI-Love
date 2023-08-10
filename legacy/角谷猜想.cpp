#include<bits/stdc++.h>
using namespace std;
int main(){
	long long int number;
	scanf("%lld",&number);
	while(true){
		if(number==1){
			printf("End");
			return 0;
		}
		if(number%2==0){
			number=number/2;
			printf("%lld/2=%lld\n",2*number,number);
		}else{
			number=number*3+1;
			printf("%lld*3+1=%lld\n",(number-1)/3,number);
		}
	} 
	return 0;
}
