#include<iostream>
using namespace std;
int main(){
	long long int a,b,c;
	cin>>a>>b>>c;
	if(a<b){
		long long int temp=a;
		a=b;
		b=temp;
	}
	if(c>=a-b){
		c-=a-b;
		b+=a-b;
		if(c>0){
			a+=c/2;
			b+=c/2;
			/*
			c=0;
			*/
		}
	}else{
		b+=c;
		/*
		c=0;
		*/
	}
	long long int i=0;
	while(b-i>=0){
		i++;
		b-=i;
	}
	cout<<i;
	return 0;
} 
