#include<iostream>
using namespace std;
bool data[101];
int main(){
	int n,m;
	cin>>n>>m;
	int tmp=0,s=0,a=0;
	while(a!=n){
		tmp++;
		if(tmp==n+1){
			tmp=1;
		}
		if(data[tmp]==0){
			s+=1;
		}
		if(s==m){
			s=0;
			cout<<tmp<<" ";
			data[tmp]=1;
			a++;
		}
	}
	return 0;
}