#include<bits/stdc++.h>
using namespace std;
int main(){
	double m,h,ans;
	cin>>m>>h;
	ans=m/(pow(h,2));
	if(ans<18.5){
		cout<<"Underweight";
	}else if(ans>24){
		cout<<ans<<endl<<"Overweight";
	}else{
		cout<<"Normal";
	}
	return 0;
}
