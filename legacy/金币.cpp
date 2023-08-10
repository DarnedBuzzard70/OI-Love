#include<bits/stdc++.h>
using namespace std;
int main(){
	int b;
	cin>>b;
	int alld=b;
	int day=1;
	int td=0;
	int sum=0;
	for(int i=1;i<=b;i++){
		td++;
		sum+=day;
		if(td==day){
			day++;
			td=0;
		}
	}
	cout<<sum;
	return 0;
} 
