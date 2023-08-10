#include<cstdio>
using namespace std;
int data[10000];
int main(){
    int num;
    scanf("%d",&num);
    int max=-1,min=0x8000000;
    for(int i=0;i<num;i++){
        scanf("%d",&data[i]);
        if(data[i]<min){
            min=data[i];
        }
        if(data[i]>max){
            max=data[i];
        }
    }
    printf("%d",max-min);
    return 0;
}