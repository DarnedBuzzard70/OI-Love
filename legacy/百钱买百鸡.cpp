#include<bits/stdc++.h>
using namespace std;
int main(){
	int x,y,z,x2=100/5,y2=100/3;
	for(x=0;x<=x2;x++){
		for(y=0;y<=y2;y++){
			z=100-x-y;
			if(z%3==0&&5*x+3*y+z/3==100){
				printf("%d %d %d\n",x,y,z);
			}
		}
	}
	return 0;
}

