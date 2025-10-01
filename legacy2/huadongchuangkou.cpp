#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int read_int(){
    int s=0,w=1;
    char ch=getchar();
    while(!(ch>='0'&&ch<='9')){
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
const int MAXN=1e6+10;
int n,k;
int a[MAXN],ansa[MAXN],ansb[MAXN];
deque <int> q;
signed main(){
    n=read_int(),k=read_int();
    for(int i=1;i<=n;i+=1){
        a[i]=read_int();
    }
    while(q.empty()==false){
        q.pop_front();
    }
    for(int i=1;i<=n;i+=1){
        while((q.empty()==false)&&(a[q.back()]>a[i])){
            q.pop_back();
        }
        q.push_back(i);
        if(i>=k){
            while((q.empty()==false)&&(q.front()<=i-k)){
                q.pop_front();
            }
            cout<<a[q.front()]<<" ";
        }
    }
    cout<<'\n';
    while(q.empty()==false){
        q.pop_front();
    }
    for(int i=1;i<=n;i+=1){
        while(!q.empty()&&a[q.back()]<a[i]){
            q.pop_back();
        }
        q.push_back(i);
        if(i>=k){
            while(!q.empty()&&q.front()<=i-k){
                q.pop_front();
            }
            cout<<a[q.front()]<<" ";
        }
    }
    return 0;
}