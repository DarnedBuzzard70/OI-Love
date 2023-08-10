#include<iostream>
using namespace std;
int main(){
	double h=0,tenth=0,sum=0;
	cin>>h;
	int i=0;
	while(i<10){
		if(i!=9){
			sum+=h;
			h/=2;
			sum+=h;
		}else{
			sum+=h;
			h=h/2;
			tenth=h;
		}
		i++;
	}
	cout<<sum<<endl<<tenth<<endl;
	return 0;
} 
