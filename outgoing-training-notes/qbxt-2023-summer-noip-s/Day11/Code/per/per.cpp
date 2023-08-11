#include<bits/stdc++.h>
#define For(i,x,y) for (int i=(x);i<=(y);i++)
#define FOR(i,x,y) for (int i=(x);i<(y);i++)
#define Dow(i,x,y) for (int i=(x);i>=(y);i--)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ep emplace_back
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define fil(a,b) memset((a),(b),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pa;
typedef pair<ll,ll> PA;
typedef vector<int> poly;
inline ll read(){
	ll x=0,f=1;char c=getchar();
	while ((c<'0'||c>'9')&&(c!='-')) c=getchar();
	if (c=='-') f=-1,c=getchar();
	while (c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x*f;
}

const int N = 5010, mod = 1e9+7;
int n,k,dp[N][N];

int main(){
	freopen("per.in","r",stdin);
	freopen("per.out","w",stdout);
	n=read(),k=read();
	dp[3][0]=4;
	dp[3][1]=2;
	For(i,4,n){
		For(j,0,i/2) dp[i][j]=(1ll*dp[i-1][j]*(2*j+2)+1ll*dp[i-1][j-1]*(i-(2*j)))%mod;
	}
	printf("%d\n",dp[n][k]);
}