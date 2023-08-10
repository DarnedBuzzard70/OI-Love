#include<iostream>
using namespace std;
int main(){
	int tLN,tHN;
	int tAoO=0;
	cin>>tLN>>tHN;
	for(int i=tLN;i<=tHN;i+=1){
		if(i%2!=0){
			tAoO+=i;
		}
	}
	cout<<tAoO/*<<endl*/;
	return 0;
}
