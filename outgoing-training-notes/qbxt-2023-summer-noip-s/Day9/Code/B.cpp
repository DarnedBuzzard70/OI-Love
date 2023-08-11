#include<iostream>
#include<cstdio>
using namespace std;
const int Maxn=35;
int u[Maxn][Maxn];
int rr[Maxn],rc[Maxn];
int r[Maxn],c[Maxn],n,m;
bool found;
bool check(){
    for (int i=1;i<=n;i++) if (r[i]) return false;
    for (int i=1;i<=m;i++) if (c[i]) return false;
    return true;
}

void dfs2(int x,int y){
    if (found) return;
    if (y == m + 1){
        dfs2(x + 1, 1);
        return;
    }
    if (x == n + 1){
        if (check()){
            for (int i=1;i<=n;i++){
                for (int j=1;j<=m;j++){
                    printf("%d ",u[i][j]);
                }
                printf("\n");
            }
            found = true;
            return;
        }
        return;
    }
    rr[x] -= y;rc[y] -= x;

    if (0 <= r[x] && r[x] <= rr[x] && 0 <= c[y] && c[y] <= rc[y]){

        u[x][y] = 0;
        dfs2(x,y + 1);
    }

    r[x] -= y; c[y] -= x;
    if (0 <= r[x] && r[x] <= rr[x] && 0 <= c[y] && c[y] <= rc[y]){
        u[x][y] = 1;
        dfs2(x,y + 1);
    }
    r[x] += y; c[y] += x;

    rr[x] += y; rc[y] += x;

}

void dfs(int x,int y){
    if (found) return;
    if (y==0){
        dfs(x - 1, m);
        return;
    }
    if (x==0){
        if (check()){
            for (int i=1;i<=n;i++){
                for (int j=1;j<=m;j++){
                    printf("%d ",u[i][j]);
                }
                printf("\n");
            }
            found = true;
            return;
        }
        return;
    }
    rr[x]-=y;rc[y]-=x;

    if (0 <= r[x] && r[x] <= rr[x] && 0 <= c[y] && c[y] <= rc[y]){

        u[x][y] = 0;
        dfs(x,y - 1);
    }

    r[x] -= y; c[y] -= x;
    if (0 <= r[x] && r[x] <= rr[x] && 0 <= c[y] && c[y] <= rc[y]){
        u[x][y] = 1;
        dfs(x,y - 1);
    }
    r[x] += y; c[y] += x;

    rr[x] += y; rc[y] += x;

}
void mian(){
    cin>>n>>m;

    //int tot=0, av = 0;
    for (int i=1;i<=n;i++){
        cin>>r[i];
        //tot+=r[i];
        rr[i]=m*(m+1)/2;
        //av += rr[i] / 2;
    } 
    for (int i=1;i<=m;i++){
        cin>>c[i];
        rc[i]=n*(n+1)/2;
        //tot+=c[i];
        //av += rc[i] / 2;
    } 
    found = false;

    dfs(n,m);
}
int main(){
    int T;
    cin>>T;
    while (T--){
        mian();
    }
}