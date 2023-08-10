#include<iostream>
#include<cmath>
using namespace std;
int main(){
	double x,y;
	double time=0;
	int len,r;
	cin>>len;
	double sum=0;
	for(int i=0;i<len;i+=1){
		cin>>x>>y>>r;
		sum+=sqrt(pow(x,2)+pow(y,2));
		time+=1.5*r+sum/(50/2);
	}
	cout<<ceil(time)<<endl;
	return 0;
}
