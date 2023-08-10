#include <iostream>
using namespace std;
int main(){
	int sum=0,sum2=0;
	for(int i=1;i<=100;i+=1){
		if(i%2==1){
			sum+=i;
		}else{
			sum2+=i;
		}
	}
	cout<<sum<<endl; 
	cout<<sum2<<endl;
	return 0; 
} 
