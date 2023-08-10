#include<bits/stdc++.h>
using namespace std;
int data[10];
bool cmp(int x,int y){
	return x<y; 
}
int main(){
	for(int i=0;i<10;i++){
		scanf("%d",&data[i]);
	}
	sort(data,data+10,cmp);
	for(int i=0;i<10;i++){
		printf("%d ",data[i]);
	}
	return 0;
}
