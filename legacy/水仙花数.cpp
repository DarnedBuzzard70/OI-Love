#include<bits/stdc++.h>
using namespace std;
bool sxh(int i){
	int b=i,c=0;
	while(b!=0){
		int temp=b%10;
		b/=10;
		c+=pow(temp,3);
	}
	if(c==i){
		return true;
	}else{
		return false;
	}
}
int main(){
	for(int i=100;i<1000;i+=1){
		if(sxh(i)){
			printf("%d ",i);
		}
	} 
	return 0;
}
