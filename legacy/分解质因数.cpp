#include <iostream>
using namespace std;
int main(){
	unsigned long long int n,i=2;
	cin>>n;
	cout<<n<<"=";
	do{
		while(n%i==0){
			cout<<i;n/=i;
			if(n!=1){
				cout<<"¡Á";
			}
		}
		i++;
	}
	while(n!=1);
	return 0;
}
