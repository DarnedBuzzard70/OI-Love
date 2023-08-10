#include<iostream>
using namespace std;
int data[46];
int FIB(int b){
	data[1]=1;
	data[0]=1;
	for(int i=2;i<46;i++){
		data[i]=data[i-1]+data[i-2];
	}
	return data[b-1];
}
int main(){
	int b;
	cin>>b;
	cout<<FIB(b)<<endl;
	return 0;
}
