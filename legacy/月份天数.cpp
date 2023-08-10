#include<bits/stdc++.h>
using namespace std;
bool run(int b){
	if(b%4==0&&(b%400==0||b%100!=0)){
		return true;
	}else{
		return false;
	}
}
int main(){
	int b,c;
	cin>>b>>c;
	switch(c){
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:					
		case 12:
			cout<<"31";
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			cout<<"30";
			break;
		case 2:
			if(run(b)){
				cout<<"29";
			}else{
				cout<<"28"; 
			}
			break;
	}
	return 0;
}
