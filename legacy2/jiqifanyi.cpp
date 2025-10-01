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
const int MAXN=1e3+10;
int n,m,cnt ;
int h[MAXN];
queue<int> mem;
int main(){
    // m=read_int(),n=read_int();
    cin>>m>>n;
    for(int ki=1;ki<=n;ki+=1){
        // int en=read_int();
        int en;
        cin>>en;
        if(!h[en]){
            cnt+=1;
            mem.push(en);
            h[en]=1;
            while(mem.size()>m){
                int tp=mem.front();
                h[tp]=0;
                mem.pop();
            }
        }
    }
    cout<<cnt;
    return 0;
}