#include<cstdio>
using namespace std;
int main(){
    int a;
    scanf("%d",&a);
    int i=0;
    for(;a>1;i++){
        a/=2;
    }
    printf("%d",i+1);
    return 0;
}