#include <bits/stdc++.h>
char result[8];
using namespace std;
int main(){
	int data;
	cin>>data;
	if(data%3==0){
		result[0]='3';
		if(data%5==0){
			result[1]=' ';
			result[2]='5';
			if(data%7==0){
				result[3]=' ';
				result[4]='7';
			}
		}else if(data%7==0){
			result[1]=' ';
			result[2]='7';
		}
	}else if(data%5==0){
		result[0]='5'; 
		if(data%7==0){
			result[1]=' ';
			result[2]='7';
		}
	}else if(data%7==0){
		result[0]='7'; 
	}else{
		result[0]='n'; 
	}
	printf("%s",result);
	return 0;
}  
