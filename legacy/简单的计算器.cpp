#include <bits/stdc++.h>
using namespace std;
int main(){
	double num1=0,num2=0;
	char op;
	cin>>num1>>num2>>op;
	if(op=='+'){
		cout<<num1+num2;
	}else if(op=='-'){
		cout<<num1-num2;
	}else if(op=='*'){
		cout<<num1*num2;
	}else if(op=='/'){
		if(num2!=0)
		cout<<num1/num2;
		else
		cout<<"Divided by zero!"; 
	}else{
		cout<<"Invalid operator!";
	}
	return 0;
}
