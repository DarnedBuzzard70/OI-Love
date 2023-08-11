#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define int ll
#define rng(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,b) rng(i,0,b)
#define gnr(i,a,b) for(int i=int(b)-1;i>=int(a);i--)
#define per(i,b) gnr(i,0,b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#define si(x) int(x.size())
template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;
using pi=pair<int,int>;
using vi=vc<int>;
#define mp make_pair
ll read(){
	ll i;
	cin>>i;
	return i;
}
vi readvi(int n,int off=0){
	vi v(n);
	rep(i,n)v[i]=read()+off;
	return v;
}
bool inc(int a,int b,int c){
	return a<=b&&b<=c;
}
template<class E>
struct doubling{
	const vvc<E>&g;
	const int n,h;
	int cnt;
	vvc<int> par;
	vi dep,in,out;
	void dfs(int v,int p,int d){
		par[0][v]=p;
		dep[v]=d;
		in[v]=cnt++;
		for(auto e:g[v])if(e!=p)
			dfs(e,v,d+1);
		out[v]=cnt;
	}
	doubling(const vvc<E>&gg,int r):g(gg),n(g.size()),h(log2(n)+1),
		cnt(0),par(h,vi(n,-1)),dep(n),in(n),out(n){
		dfs(r,-1,0);
		rng(i,1,h){
			rep(j,n)
				if(par[i-1][j]!=-1)
					par[i][j]=par[i-1][par[i-1][j]];
		}
	}
	int lca(int a,int b){
		if(dep[a]>dep[b])swap(a,b);
		int w=dep[b]-dep[a];
		rep(i,h)if(w&1<<i)
			b=par[i][b];
		if(a==b)return a;
		per(i,h){
			int x=par[i][a],y=par[i][b];
			if(x!=y)tie(a,b)=pi(x,y);
		}
		return par[0][a];
	}
	int len(int a,int b){
		return dep[a]+dep[b]-dep[lca(a,b)]*2;
	}
	int jump(int a,int b,int d){
		int c=lca(a,b);
		int w=dep[a]+dep[b]-dep[c]*2;
		if(d<=dep[a]-dep[c]){
			rep(i,h)if(d&1<<i)
				a=par[i][a];
			return a;
		}else{
			d=w-d;
			rep(i,h)if(d&1<<i)
				b=par[i][b];
			return b;
		}
	}
};

using A=array<int,3>;
vi getvals(int n,const vc<pi>&es,A rs){
	vvc<int> t(n);
	rep(i,n-1){
		t[es[i].a].pb(es[i].b);
		t[es[i].b].pb(es[i].a);
	}
	auto getdist=[&](int r){
		vi dist(n,-1);
		queue<int> q;
		auto reach=[&](int v,int d){
			if(dist[v]==-1){
				dist[v]=d;
				q.push(v);
			}
		};
		reach(r,0);
		while(si(q)){
			int v=q.front();q.pop();
			for(auto to:t[v])
				reach(to,dist[v]+1);
		}
		return dist;
	};
	vc<A> as(n);
	rep(k,3){
		vi d=getdist(rs[k]);
		rep(i,n)as[i][k]=d[i];
	}
	vi res(n);
	rep(i,n){
		sort(all(as[i]));
		res[i]=as[i][1];
	}
	return res;
}

bool dbg=false;

void solve(){
	int n;
	cin>>n;
	vc<pi> es;
	rep(i,n-1) es.eb(i+1,read()-1);
	vi val;
	val=readvi(n);
	vi valraw=val;
	val.resize(n+n-1);
	vvc<int> t(n+n-1);

	auto ae=[&](int a,int b){
		t[a].pb(b);
		t[b].pb(a);
	};
	vi waf;
	rep(i,n-1){
		int a,b;tie(a,b)=es[i];
		int d=abs(val[a]-val[b]);
		if(d>1){
			cout<<0<<endl;
			return;
		}
		if(d==0){
			waf.pb(i);
		}else{
			val[n+i]=val[a]+val[b];
		}
		ae(a,n+i);
		ae(b,n+i);
	}
	rep(i,n)val[i]*=2;
	
	if(si(waf)>5){
		cout<<0<<endl;
		return;
	}
	n=n*2-1;
	
	int ans=0;
	
	doubling<int> ysp(t,0);
	
	rep(bit,1<<si(waf)){
		rep(i,si(waf)){
			int x=waf[i];
			int a,b;tie(a,b)=es[x];
			if(bit&1<<i){
				val[(n+1)/2+x]=val[a]-1;
			}else{
				val[(n+1)/2+x]=val[a]+1;
			}
		}
		
		int pa=-1,pb=-1;
		
		bool ng=false;
		
		rep(i,n){
			bool mn=true;
			for(auto j:t[i]){
				if(val[j]<val[i])mn=false;
			}
			if(mn){
				if(pa==-1){
					pa=i;
				}else if(pb==-1){
					pb=i;
				}else{
					ng=true;
				}
			}
		}
		
		if(!ng){
			int tar;
			auto dfs=[&](auto self,int v,int p,int d)->pi{
				int a=0,b=0;
				if(v<=n/2){
					if(tar==d)a++;
					else if(tar<d)b++;
				}
				for(auto to:t[v]){
					if(to!=p){
						int x,y;tie(x,y)=self(self,to,v,d+1);
						a+=x;
						b+=y;
					}
				}
				return pi(a,b);
			};
			if(pb==-1){
				tar=val[pa];
				assert(tar>0);
				int dp[4][2]{};
				dp[0][0]=1;
				for(auto v:t[pa]){
					int a,b;tie(a,b)=dfs(dfs,v,pa,1);
					per(x,4)per(y,2){
						if(x+1<4)dp[x+1][y]+=dp[x][y]*a;
						if(y+1<2)dp[x][y+1]+=dp[x][y]*b;
					}
				}
				ans+=dp[3][0];
				ans+=dp[2][1];
			}else{
				int len=ysp.len(pa,pb);
				int sum=val[pa]+val[pb];
				if(sum>=len&&(sum-len)%2==0){
					int z=(sum-len)/2;
					int k=val[pa]-z;
					if(inc(1,k,len-1)){
						int w=1;
						rep(_,2){
							tar=val[pa];
							int x=dfs(dfs,pa,ysp.jump(pa,pb,1),0).a;
							w*=x;
							swap(pa,pb);
						}
						{
							int pc=ysp.jump(pa,pb,k);
							int nga=ysp.jump(pc,pa,1);
							int ngb=ysp.jump(pc,pb,1);
							int x=0;
							tar=z;
							if(tar==0){
								x=1;
							}else{
								for(auto to:t[pc]){
									if(to!=nga&&to!=ngb){
										x+=dfs(dfs,to,pc,1).a;
									}
								}
							}
							w*=x;
						}
						ans+=w;
					}
				}
			}
		}
	}
	cout<<ans<<endl;
}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	int T;cin>>T;
	while (T--){
		//cerr<<123<<endl;
		solve();
	}
	return 0;
}
