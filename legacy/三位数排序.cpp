#include<bits/stdc++.h>
int data[3];
using namespace std;
int main(){
	for(int i=0;i<3;i++){
		cin>>data[i];
	}
	sort(data,data+3);
	for(int i=0;i<3;i++){
		cout<<data[i]<<" ";
	}
	return 0;
}
