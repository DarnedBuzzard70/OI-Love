#include<cstdio>
using namespace std;
int b;
int exch(int time){
    if(time==b){
        return 0;
    }else{
        time++;
        int temp;
        scanf("%d",&temp);
        exch(time);
        printf("%d ",temp);
        return 0;
    }
}
int main(){
    scanf("%d",&b);
    int time=0;
    exch(time);
    return 0;
}