### 清北学堂 Day 10 总结

------------

## 材料准备

- 题目链接：[LINK](https://noip.ac/rs/problemset/show/261)

## 题解 & 思路

### T1

- 题目内容

	小 $A$ 居住在风景优美的下北泽，城市里由 $n$ 个路口和 $m$ 条双向道路连通, 每个路口都有一个红绿灯, 绿灯表示可以选择一个道路通行，红灯表示需要在当前的路口等待。初始所有路口都是绿灯, $k$ 秒后所有路口会变成红灯, 再 $k$ 秒后所有路口又会变回绿灯, 如此往复。

	如果在刚到某个路口的时候正好灯的颜色正在转换，那么以转换之后的颜色为准。

	现在小 $A$ 想要从 $1$ 号路口走到 $n$ 号路口, 求他最少需要的时间，保证至少存在一条从 $1$ 号路口到 $n$ 号路口的路径。
    
- 题解

	直接迪杰斯特拉单元最短路魔改一下就行。
    
- AC Code

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
const int MAXN=1e4+10,MAXM=2e5+10;
struct p {
	int dis;
	int u;
};
bool operator< (const p &a,const p &b) {
	return a.dis>b.dis;
}
int cnt=0,head[MAXN];
int nxt[MAXM],val[MAXM],to[MAXM];
int n,m,k;
int dis[MAXN],vis[MAXN];
void add_edge(int u,int v,int w) {
	cnt+=1;
	nxt[cnt]=head[u];
	to[cnt]=v;
	val[cnt]=w;
	head[u]=cnt;
}
void dijkstra(int st) {
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[st]=0;
	priority_queue<p>q;
	q.push((p) {0,st});
	while(!q.empty()) {
		int u=q.top().u;
		int currentTime=q.top().dis; 
		q.pop();
		if(vis[u]) {
			continue;
		}
		vis[u]=1;
		for(int i=head[u]; i!=0; i=nxt[i]) {
			int v=to[i];
//			int currentTime=q.dis; 
            int wait=currentTime%(2*k)>=k?2*k-currentTime%(2*k):0;
			if(dis[v]>dis[u]+val[i]+wait) {
				dis[v]=dis[u]+val[i]+wait;
				q.push((p) {dis[v],v});
			}
		}
	}
	return;
}
signed main() {
	n=read_int();
	k=read_int();
	m=read_int();
	for(int k1=1; k1<=m; k1+=1) {
		int u=read_int();
		int v=read_int();
		int w=read_int();
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dijkstra(1);
	printf("%lld\n",dis[n]);
	return 0;
}
```

### T2 & T3 & T4

见 GitHub 仓库。

## 标程

见 GitHub 仓库。