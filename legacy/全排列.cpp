#include<bits/stdc++.h>
using namespace std;
int a[100];
int flag[100];
int n;
void f(int k){
	if(k==0){
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
		return;
	}
	for(int i=1;i<=n;i+=1){
		if(flag[i]==0){
			flag[i]=1;
			a[k]=n-i+1;
			f(k-1);
			flag[i]=0;
		}
	}
}
int main(){
	cin>>n;
	f(n);
	return 0;
}
