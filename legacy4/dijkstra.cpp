#include<bits/stdc++.h>
#define int long long 
using namespace std;

/*
常量 MAXN 表示最大节点数量，此处应至少多开两个。
常量 MAXM 表示最大有向边数量，此处应至少多开两个，如果是用有向边模拟无向边，需要开两倍。
*/
const int MAXN=2e5+10;
const int MAXM=5e5+10;

/*
快速读入，此处是个人代码习惯，重定义 int 为 long long 类型时，可读如 long long 类型整数。
*/
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

/*
定义结构体 p，包含 dis 和 u 两个成员，分别表示距离和节点编号。
*/
struct p{
	int dis;
	int u;
};

/*
重载小于运算符，方便使用优先队列。
*/
bool operator< (const p &a,const p &b){
	return a.dis>b.dis;
} 

/*
链式前向星存图。
*/
int cnt=0,head[MAXN];
int nxt[MAXM],val[MAXM],to[MAXM];
int n,m,s;
int dis[MAXN],vis[MAXN];

/*
add_edge函数负责链式前向星的加边。
*/
void add_edge(int u,int v,int w){
	cnt+=1;
	nxt[cnt]=head[u];
	to[cnt]=v;
	val[cnt]=w;
	head[u]=cnt;
}

/*
dijkstra函数：从起点 st 出发，计算单源最短路。
使用优先队列维护当前距离最小的点，并用 vis 数组避免重复扩展。
*/
void dijkstra(int st){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[st]=0;
	priority_queue<p>q;
	q.push((p){0,st});
	while(!q.empty()){
		/*
        取出当前距离最小的节点 u，如果已经访问过则跳过，否则标记为已访问，并松弛其相邻边。
        */
		int u=q.top().u;
		q.pop();
		if(vis[u]){
			continue;
		}
		vis[u]=1;
		for(int i=head[u];i!=0;i=nxt[i]){
			int v=to[i];
			/*
            松弛相邻边，若找到更短路径就更新并重新入队
            */
			if(dis[v]>dis[u]+val[i]){
				dis[v]=dis[u]+val[i];
				q.push((p){dis[v],v});
			}
		}
	}
	return;
}
signed main(){
    freopen("dijkstra.in","r",stdin);   //重定向输入，从文件 "dijkstra.in" 中读取。
    freopen("dijkstra.out","w",stdout); //重定向输出，将结果写入文件 "dijkstra.out" 中。
	n=read_int();
	m=read_int();
	s=read_int(); 
	for(int i=1;i<=m;i+=1){
		int u=read_int();
		int v=read_int();
		int w=read_int();
		add_edge(u,v,w);
	}
	dijkstra(s);
	for(int i=1;i<=n;i+=1){
		printf("%lld \n",dis[i]);
	}
	return 0;
}