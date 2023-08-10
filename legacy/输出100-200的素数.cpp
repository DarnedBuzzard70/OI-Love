#include<bits/stdc++.h>
using namespace std;
int main(){
	int temp=sqrt(200);
	for(int i=100;i<=200;i++){
		bool flag=true;
		for(int j=2;j<temp;j++){
			if(i%j==0){
				flag=false;
				break;
			}
		}
		if(flag==true){
			printf("%d\t",i);
		}
	}
	return 0;
}
