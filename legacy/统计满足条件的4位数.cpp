#include<iostream>
using namespace std;
void FtN(int &NoN,int temp){
	int b=temp;
	int flag=0;
	int data[4];
	while(b!=0){
		data[flag]=b%10;
		flag+=1;
		b/=10;
	}
	if(data[1]-data[2]-data[3]-data[4]>0){
		NoN+=1;
	}
}
int main(){
	int len;
	int temp;
	cin>>len;
	int NoN=0; 
	for(int i=0;i<len;i+=1){
		cin>>temp;
		FtN(NoN,temp);
	}
	cout<<NoN<<endl;
	return 0;
} 
