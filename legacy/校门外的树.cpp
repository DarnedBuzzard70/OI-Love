#include<cstdio>
using namespace std;
int data[10005];
int main(){
    int M,L;
    scanf("%d%d",&L,&M);
    for(int i=0;i<M;i++){
        int Sta,End;
        scanf("%d%d",&Sta,&End);
        for(int j=Sta;j<=End;j++){
            data[j]=1;
        }
    }
    int ans=0;
    for(int i=0;i<=L;i++){
        if(data[i]==0){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}