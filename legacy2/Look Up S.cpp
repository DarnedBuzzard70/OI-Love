#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read_int(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            w=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=10*s+ch-'0';
        ch=getchar();
    }
    return s*w;
}
const int MAXN=1e5+10;
int n;
int ans[MAXN],h[MAXN];
stack <int> q;
signed main(){
    n=read_int();
    for(int i=1;i<=n;i+=1){
        h[i]=read_int();
    }
    for(int i=n;i>=1;i-=1){
        while(!q.empty()&&h[q.top()]<=h[i]){
            q.pop();
        }
        if(q.empty()){
            ans[i]=0;
        }else{
            ans[i]=q.top();
        }
        q.push(i);
    }
    for(int i=1;i<=n;i+=1){
        printf("%lld\n",ans[i]);
    }
    return 0;
}