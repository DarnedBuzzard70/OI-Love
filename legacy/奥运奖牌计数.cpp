#include<bits/stdc++.h>
using namespace std;
int main(){
	int len;
	cin>>len;
	int temp;
	int jin=0;
	int yin=0;
	int tong=0;
	for(int i=0;i<len;i+=1){
		cin>>temp;
		jin+=temp;
		cin>>temp;
		yin+=temp;
		cin>>temp;
		tong+=temp;
	}
	cout<<jin<<" "<<yin<<" "<<tong<<" "<<jin+yin+tong<<endl;
	return 0; 
} 
