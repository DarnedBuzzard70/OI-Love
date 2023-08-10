#include<bits/stdc++.h>
using namespace std;
int main(){
	int a,b,c,x,y,counter=0;
	cin>>a>>b>>c;
	for(x=0;x<=c/a;x++){
		for(y=0;y<=c/b;y++){
			if(a*x+b*y==c){
				counter++;
			}
		}
	}
	cout<<counter;
	return 0;
}
