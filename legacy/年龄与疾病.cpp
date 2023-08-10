#include<cstdio>
using namespace std;
double  data[4];
int main(){
    int b;
    scanf("%d",&b);
    for(int i=0;i<b;i++){
        int temp;
        scanf("%d",&temp);
        if(temp<=18){
            data[0]+=100;
        }else if(temp<=35){
            data[1]+=100;
        }else if(temp<=60){
            data[2]+=100;
        }else{
            data[3]+=100;
        }
    }
    for(int i=0;i<4;i++){
        printf("%.2lf\%\n",data[i]/b);
    }
    return 0;
}