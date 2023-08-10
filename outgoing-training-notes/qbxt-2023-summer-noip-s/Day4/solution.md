### 清北学堂 Day 4 总结

------------

## 背景

```
901 范丽丽：

从今天开始，要求大家每天在群里提交一份今日总结，包含四个内容：
1、每天比赛的四个题的题解（简单思路+代码）
2、当天讲课的内容的简单笔记
3、当天讲课涉及到的题单，备注已完成或待完成
4、对今天比赛和听课的一个简单总结。
```

## 材料准备

- 题目链接：[LINK](https://noip.ac/rs/problemset/show/246)

## 题解 & 思路

### T1 

- 题意简化

给定一个 n 个点的有根树，询问有几个点的子树大小超过整个树的一半。
$1 \le n \le 3 \times 10^5$。

- 思路分析

由根向子树统计，做深度优先搜索即可，复杂度为 $O(n)$。
做深度优先搜索时要注意初始值应赋值为 $0$。

- 赛时代码

```cpp
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
const int MAXN=3e5+10;
int fa[MAXN],son[MAXN];
int ans;
struct {
	vector<int> s;
} db[MAXN];
int dfs(int p) {
	if(son[p]!=-1) {
		return son[p];
	}
	son[p]=0;
	int n=db[p].s.size();
	if(n==0) {
		return 0;
	}
	for(int i=0; i<n; i+=1) {
		son[p]+=(dfs(db[p].s[i])+1);
	}
	return son[p];
}
signed main() {
	memset(son,-1,sizeof(son));
	int n=read_int();
	for(int i=2; i<=n; i+=1) {
		fa[i]=read_int();
		db[fa[i]].s.push_back(i);
	}
	int d=sqrt(n);
	for(int i=n;i>=1;i-=d){
		dfs(i);
	} 
	son[1]=dfs(1);
	for(int i=1; i<=n; i+=1) {
		if(son[i]*2>=n) {
			ans+=1;
		}
	}
	printf("%lld \n",ans);
	return 0;
}
```
### T2

- 题意简化

定 $[1, n] ∩ Z$ 的一个子集 $S$，询问若 $i$ 的父亲在 $[1, i − 1]$ 中等概率生成，
S 中的点从上到下形成一条链的概率，$q$ 次询问。
$1 \le n, q \le 3 \times 10^5$，询问的子集大小总和不超过 $3 \times 10^5$。

- 思路分析

假如 $S$ 中点从小到大依次为 $x_1, x_2, . . . , x_m$，可以发现“$x_i$ 是 $x_{i+1}$ 的祖先”这些事件之间是互相独立的。然后通过计算，发现 $x_i$ 是 $x_{i+1}$ 的祖先的概率和 $x_{i+1}$ 具体是什么无关：
我们令 $x_{i+1}$ 一直跳父亲，直到编号小于等于 $x_i$ 的那一次。因为父亲是等概率选取的，所以概率就是 $\frac{1}{x_i}$。
同时，对于原题答案即为 $\prod{m-1}{i=1}x_i$
总复杂度 $O(n +\Sigma{}{}k_i)$。

### T3 & T4

由于难度问题和考试范围，就先不写了，有时间再写。

## 标程

### T1

```cpp
#include <bits/stdc++.h>
const int mod=998244353;
using namespace std;
int n,sz[300010],ans=0;
vector<int>E[300010];
void dfs(int u){
	sz[u]=1;
	for(int v:E[u]){
		dfs(v);
		sz[u]+=sz[v];
	}
	if(2*(sz[u]-1)>=n) ans++;
}
int main(){
	scanf("%d",&n);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),E[fa].push_back(i);
	dfs(1);
	printf("%d\n",ans);
}
```

### T2

```cpp
#include <bits/stdc++.h>
#define No() puts("NO"),exit(0)
using namespace std;
int head[300010],o=0,n,m,u[300010],v[300010],ecnt=0;
bool vis[300010],usd[300010];
struct edge{
	int to,link,w;
}e[600010];
void add_edge(int u,int v,int w){
	e[++o]={v,head[u],w},head[u]=o;
	e[++o]={u,head[v],w},head[v]=o;
}
void dfs(int u){
	vis[u]=1;
	for(int i=head[u];i;i=e[i].link) if(!usd[e[i].w]) usd[e[i].w]=1,ecnt++;
	for(int i=head[u],v;i;i=e[i].link) if(!vis[v=e[i].to]) dfs(v);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) 		       scanf("%d%d",&u[i],&v[i]),add_edge(u[i],v[i],i);
	for(int i=1;i<=n;i++) if(!vis[i]){
		ecnt=0,dfs(i);
		if(ecnt&1) No();
	}
	puts("YES");
}
```
### T3

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n,m,k,a[300010],L[300010],R[300010],st[300010],t=0,cnt=0;
ll ans=0,len[300010],c[300010];
vector<int>E[300010];
void dfs(int u){
	int son=0;
	for(int v:E[u]){
		dfs(v);
		if(len[v]>len[son]) son=v;
	}
	len[u]=len[son]+a[u];
	for(int v:E[u]) if(son^v) c[cnt++]=len[v];
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),L[i]=i+1,ans+=a[i];
	for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r),L[r]=min(L[r],l);
	for(int i=n;i>=1;i--){
		while(t&&L[i]<=L[st[t]]) t--;
		if(L[i]<=i) st[++t]=i;
		if(t&&L[st[t]]<=i) R[i]=st[t];
		else ans-=a[i],R[i]=i-1;
	}
	st[t=1]=0,R[0]=n;
	for(int i=1;i<=n;i++){
		while(t&&R[st[t]]<i) t--;
		if(R[i]>=i) E[st[t]].push_back(i),st[++t]=i;
	}
	dfs(0),c[cnt++]=len[0];
	if(cnt>=k) nth_element(c,c+cnt-k,c+cnt);
	for(int i=max(cnt-k,0);i<cnt;i++) ans-=c[i];
	printf("%lld\n",ans);
}
```

### T4

```cpp
#include <bits/stdc++.h>
const int mod=998244353;
using namespace std;
int inv[300010];
void init(int N){
	inv[1]=1;
	for(int i=2;i<=N;i++) inv[i]=mod-1ll*inv[mod%i]*(mod/i)%mod;
}
int main(){
	int n,q,w;
	scanf("%d%d",&n,&q),init(n);
	while(q--){
		scanf("%d",&n);
		int ans=1,mx=0;
		while(n--) scanf("%d",&w),ans=1ll*ans*inv[w]%mod,mx=max(mx,w);
		printf("%d\n",1ll*ans*mx%mod);
	}
}
```

------------

## 一些奇技淫巧

### 随机树（数）据

在题目中树为纯随机生成时，会有一些额外的性质：

- 当第 i 个点的父亲在 $[1, i − 1]$ 中等概率随机选取，那么树的高度期望为 $O(log n)$。

- 当树从所有有标号无根树中随机选取，那么树的高度期望为 $O(\sqrt{n})$。

------------

## 结尾 & 一些彩蛋

[![](https://pic.imgdb.cn/item/64c264d11ddac507cc82d279.jpg)](https://pic.imgdb.cn/item/64c264d11ddac507cc82d279.jpg)

上文的图片中的图片：

[![](https://pic.imgdb.cn/item/64c264ed1ddac507cc82ff7f.jpg)](https://pic.imgdb.cn/item/64c264ed1ddac507cc82ff7f.jpg)

**希望大家理性发言！**

------------

## $\color{Plum}\texttt{Copyrights}$

```
This note is only for learning.
Without permission, it is prohibited to use it for other commercial or non commercial purposes.
Zhang Yucheng reserves all rights.
```

------------

 $$\color{Plum}\texttt{The End by DarnedBuzzard70}$$