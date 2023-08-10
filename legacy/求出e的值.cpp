#include<cstdio>
using namespace std;
int main(){
	double e=1.0,b,he=1.0;
	scanf("%lf",&b);
	for(int i=1;i<=b;i++){
	he*=i;
	e+=1.0/he;
	}
	printf("%.10lf",e);
	return 0;
}

