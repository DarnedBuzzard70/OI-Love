#include<cstdio>
using namespace std;
int main(){
    int n,m,s;
    scanf("%d%d",&n,&m);
    printf("1");
    for(int i=2;i<=n;i++){
        s=-1;
        for(int j=2;j<=m;j++){
            if(i%j==0){
                s=-s;
            }
        }
        if(s==-1){
           printf(",%d",i);
        }
    }
    return 0;
}