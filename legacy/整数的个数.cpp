#include<iostream>
using namespace std;
int main(){
	int len;
	cin>>len;
	int NoO=0;
	int NoF=0;
	int NoT=0;
	cin>>len;
	for(int i=0;i<len;i+=1){
		int temp=0;
		cin>>temp;
		if(temp==1){
			NoO+=1;
		}else if(temp==5){
			NoF+=1;
		}else if(temp==10){
			NoT+=1;
		}
	}
	cout<<NoO<<endl<<NoF<<endl<<NoT;
	return 0;
}
