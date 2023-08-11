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

const int N = 5e5+10;
int n;
PA a[N];
ll pre[N];

int main(){
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
	n=read();
	For(i,1,n) a[i].fi=read(),a[i].se=read();
	sort(a+1,a+1+n);
	For(i,1,n) pre[i]=pre[i-1]+a[i].se;
	ll ans=0,mn=1e18;
	For(i,1,n){
		mn=min(mn,pre[i-1]-a[i].fi);
		ans=max(ans,pre[i]-a[i].fi-mn);
	}
	printf("%lld\n",ans);
}