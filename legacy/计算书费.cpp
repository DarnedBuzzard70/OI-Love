#include<cstdio>
using namespace std;
double data[11]={0,28.9,32.7,45.6,78,35,86.2,27.8,43,56,65};
int main(){
    for(int i=1;i<11;i++){
        int temp;
        scanf("%d",&temp);
        data[0]+=temp*data[i];
    }
    printf("%.1lf",data[0]);
    return 0;
}