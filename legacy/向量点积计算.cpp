#include<cstdio>
using namespace std;
int data[1010],data2[1020];
int main(){
    int b;
    scanf("%d",&b);
    int sum=0;
    for(int i=1;i<=b;i++){
        scanf("%d",&data[i]);
    }
    for(int i=1;i<=b;i++){
        scanf("%d",&data2[i]);
    }
    for(int i=1;i<=b;i++){
        scanf("%d%d",&data[i],&data2[i]);
        sum+=data[i]*data2[i];
    }
    printf("%d",sum);
    return 0;
}