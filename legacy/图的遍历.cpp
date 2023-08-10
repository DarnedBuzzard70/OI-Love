#include <cstdio>
#include <vector>
using namespace std;
vector<int> G[100010];
int N,M,A[100010];
/*
struct Edge{
    int from=-1;
    int to=-1;
    int vis=0;
    bool alive=false;
};
Edge data[100001];
*/
void dfs(int x,int d){
    if(A[x]!=0){
        return;
    }
    A[x]=d;
    for(int i=0;i<G[x].size(); i++){
		dfs(G[x][i],d);
    }
    return;
}
int main(){
    scanf("%d%d",&N,&M);
    for (int i=1;i<=M ;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        /*
        data[u].from=u;
        data[u].to=v;
        data[u].alive=true;
        */
        G[v].push_back(u);
    }
    for(int i=N; i; i-=1){
        dfs(i, i);
    }
    for(int i=1; i<=N; i++){
        printf("%d ",A[i]);
    }
    return 0;
}