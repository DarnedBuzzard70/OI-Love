#include <bits/stdc++.h>
using namespace std;
int main(){
	int Chinese=0;
	int Mathematics=0;
	cin>>Chinese>>Mathematics;
	int jige=0;
	if(Chinese>=60){
		jige+=1;
	}
	if(Mathematics>=60){
		jige+=1;
	}
	if(jige==1){
		cout<<"1";
	}else{
		cout<<"0"; 
	}
	return 0;
}

