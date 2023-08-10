#include <iostream>
using namespace std;
int data[3];
int main(){
	for(int i=0;i<3;i+=1){
		cin>>data[i]; 
    }
	for(int i=0;i<3;i+=1){	
		for(int j=0;j<3;j+=1){
			if(data[j]<data[j+1]){
				int temp=0;
				temp=data[j];
				data[j]=data[j+1];
				data[j+1]=temp;
			}
		}
	}
	for(int i=0;i<3;i+=1){
		cout<<data[i]<<endl; 
    }	
	return 0;
} 
