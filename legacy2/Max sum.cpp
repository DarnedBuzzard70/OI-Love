#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read_int() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=10*s+ch-'0';
		ch=getchar();
	}
	return s*w;
}
const int MAXN=1e5+10;
int n,t;
int dp[MAXN];
signed main() {
	t=read_int();
    for(int ki=1;ki<=t;ki+=1){
        n=read_int();
        for(int i=1;i<=n;i+=1){
            dp[i]=read_int();
        }
        int st=1,ed=1,p=1,ms=dp[1];
        for(int i=2;i<=n;i+=1){
            if(dp[i-1]+dp[i]>=dp[i]){
                dp[i]=dp[i-1]+dp[i];
            }else{
                p=i;
            }
            if(dp[i]>ms){
                ms=dp[i];
                st=p;
                ed=i;
            }

        }
        printf("Case %d:\n%d %d %d \n",ki,ms,st,ed);
        if(ki!=t){
            puts("");
        }
    }
	return 0;
}

