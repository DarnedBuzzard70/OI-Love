#include<bits/stdc++.h>
#define int long long
using namespace std;

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
常量 MAXN 表示最大节点数量，此处应至少多开两个。
n, m 分别表示点数和边数
G表示图
*/
const int MAXN = 1e3 + 5;
int n, m;
int G[MAXN][MAXN];

/*
zycBuild 函数功能是建立双向边
*/
void zycBuild(int u,int v,int w){
    G[u][v] = w;
    G[v][u] = w;
}

/*
zycRead 函数功能是读入点数、边数，和需要建立的边，使用 zycBuild 建边
*/
void zycRead(){
    n = read_int();
    m = read_int();
    int u,v,w;
    for(int i=1;i<=m;i+=1){
        u = read_int();
        v = read_int();
        w = read_int();
        zycBuild(u, v, w);
    }
}

/*
zycSolve 函数功能是使用 Floyd-Warshall 算法求解任意两点之间的最短路径长度，并将同一个点的权置为 0。
*/
void zycSolve(){
    for(int k=1;k<=n;k+=1){
        for(int i=1;i<=n;i+=1){
            for(int j=1;j<=n;j+=1){
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i+=1){
        G[i][i] = 0;
    }
}

/*
zycPrint 函数功能是打印任意两点之间的最短路径长度，如果两点之间不可达则打印 "INF"。
为观感好看，使用制表符'\t'分隔每个数值，实际使用建议改成空格。
*/
void zycPrint(){
    for(int i=1;i<=n;i+=1){
        for(int j=1;j<=n;j+=1){
            if(G[i][j] == 0x3f3f3f3f3f3f3f3f){
                printf("INF \t");
            }else{
                printf("%lld \t", G[i][j]);
            }
        }
        printf("\n");
    }
}

signed main(){
    memset(G, 0x3f, sizeof(G));                 //初始化图，使用 0x3f3f3f3f3f3f3f3f 代表无穷大。
    freopen("floyd_warshall.in","r",stdin);     //重定向输入，从文件 "floyd_warshall.in" 中读取。
    freopen("floyd_warshall.out","w",stdout);   //重定向输出，将结果写入文件 "floyd_warshall.out" 中。
    zycRead();
    zycSolve();
    zycPrint();
    return 0;
}