#include<cstdio>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    for(int i=2;true;i++){
        if(n%i==0){
            printf("%d",n/i);
            return 0;
        }
	}
    return 0; 
}
