#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,s[1001],res=0,max=-1;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>s[i];
    for(int i=1;i<=n;i++){
        if(s[i+1]-s[i]==1)res++;
        else res=0;
        if(res>max)max=res;
    }
    cout<<++max;
    return 0;
}