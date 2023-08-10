#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int main(){
int n;
cin>>n;
double a[n],sum=0,p,b[n]={0};
for(int i=0;i<n;i++){
    cin>>a[i];
}
sort(a,a+n);
a[0]=-1;
a[n-1]=-1;
for(int i=1;i<n-1;i++){
    sum+=a[i];
}
p=sum/(n-2)*1.00;
printf("%.2lf",p);
cout<<" ";
for(int i=1;i<n-1;i++){
b[i]=fabs(a[i]-p);
}
sort(b,b+n);
printf("%.2lf",b[n-1]);
return 0;
}