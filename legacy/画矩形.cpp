#include<bits/stdc++.h> 
using namespace std;
int main(){
	int height,width;
	char word;
	short parameter;
	cin>>height>>width>>word>>parameter;
	if(parameter==1){
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				cout<<word;
			}
			cout<<endl;
		}	
	}
	else{
		for(int k=0;k<width;k++){
			cout<<word;
		}
		cout<<endl;
		for(int p=0;p<height-2;p++){
			cout<<word;
			for(int o=0;o<(width-2);o++){
					cout<<" ";
				}
			cout<<word;
			cout<<endl;
		}
		for(int k=0;k<width;k++){
			cout<<word;
		}
		cout<<endl;	
	}
	return 0;
}
