#include<bits/stdc++.h>
using namespace std;
inline int read_int(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            ch=getchar();
        }
    }
    while(ch>='0'&&ch<='9'){
        s=10*s+ch-'0';
        ch=getchar();
    }
    return s*w;
}
const int MAXN=1e2+10;
int n,m;
int a[MAXN];
int main(){
    n=read_int(),m=read_int();
    for(int i=1;i<=n;i+=1){
        a[i]=(i%n)+1;
    }
    int t=1,pre=1;
    while((n--)>1){
        for(int i=1;i<m;i+=1){
            pre=t;
            t=a[t];
        }
        cout<<t<<" ";
        a[pre]=a[t];
        t=a[pre];
    }
    cout<<t;
    return 0;
}