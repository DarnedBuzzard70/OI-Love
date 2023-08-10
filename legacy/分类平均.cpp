#include<cstdio>
using namespace std;
int main(){
	int n,k,i;
	scanf("%d%d",&n,&k);
	int he=(1+n)*n/2,a=0,ji=0;
	for(i=k;i<=n;i+=k){
        a+=i,ji++;
    }
	printf("%.1lf %.1lf",a/(ji*1.00),(he-a)/((n-ji)*1.00));
	return 0;
}