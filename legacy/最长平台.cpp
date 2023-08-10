#include<bits/stdc++.h>
using namespace std;
int main(){
    int max=0,a[2000],n,i,k;
    cin>>n;
    for(i=0;i<n;i++)
    cin>>a[i];
    for(i=0;i<n;i++){
        k=count(a,a+n,a[i]);
        if(k>max)
            max=k;
    }
    cout<<max;
    return 0;
}