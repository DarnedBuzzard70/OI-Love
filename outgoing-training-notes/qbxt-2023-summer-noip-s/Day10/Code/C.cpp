#include<bits/stdc++.h>
#define LL long long
#define mp make_pair
#define pb push_back
using namespace std;
inline int read(){
    int v = 0,f = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v * f;
}
const int Maxn = 505;
int n, a[Maxn][Maxn],k;
int dist[Maxn][Maxn];
vector<pair<int,int> > pos[Maxn * Maxn];
void Ckmin(int &x,int y){
    if (y<x) x=y;
}
struct T{
    int val[Maxn * 4];
    void _init(){
        for (int i = 0;i<Maxn*4;i++) val[i]=1e9;
    }
    void modify(int p,int l,int r,int pos,int Val){
        if (l==r){
            Ckmin(val[p], Val);
            return;
        }
        int mid=l+r>>1;
        if (pos<=mid){
            modify(p*2,l,mid,pos,Val);
            Ckmin(val[p],val[p*2]);
        }
        else{
            modify(p*2+1,mid+1,r,pos,Val);
            Ckmin(val[p],val[p*2+1]);
        }
    }

    int query(int p,int l,int r,int lo,int hi){
        if (lo<=l && r<=hi){
            return val[p];
        }
        int mid=l+r>>1;
        int ans=1e9;
        if (lo<=mid){
            ans=min(ans,query(p*2,l,mid,lo,hi));
        }
        if (hi>mid){
            ans=min(ans,query(p*2+1,mid+1,r,lo,hi));
        }
        return ans;
    }

    void Modify(int pos,int Val){
        modify(1,1,n,pos,Val);
    }
    int Query(int lo,int hi){
        return query(1,1,n,lo,hi);
    }
}T1, T2;
bool cmp1(pair<int,pair<int,int> > A, pair<int,pair<int,int> > B){
    if (A.second.first != B.second.first){
        return A.second.first < B.second.first;
    }
    if (A.first != B.first){
        return A.first < B.first;
    }
    return A.second.second < B.second.second;
}

bool cmp2(pair<int,pair<int,int> > A, pair<int,pair<int,int> > B){
    if (A.second.first != B.second.first){
        return A.second.first > B.second.first;
    }
    if (A.first != B.first){
        return A.first < B.first;
    }
    return A.second.second < B.second.second;
}

void Solve(vector<pair<int,pair<int,int> > > E){
    sort(E.begin(),E.end(),cmp1);
    T1._init();T2._init();
    for (int i=0;i<E.size();i++){
        if (E[i].first == 0){
            int di = dist[E[i].second.first][E[i].second.second];
            T1.Modify(E[i].second.second, di - E[i].second.first - E[i].second.second);
            T2.Modify(E[i].second.second, di - E[i].second.first + E[i].second.second);
        }
        else{
            int &di = dist[E[i].second.first][E[i].second.second];

            Ckmin(di, T1.Query(1,E[i].second.second)+E[i].second.first+E[i].second.second);

            Ckmin(di, T2.Query(E[i].second.second,n)+E[i].second.first-E[i].second.second);
        }
    }

    sort(E.begin(),E.end(),cmp2);
    T1._init();T2._init();

    for (int i=0;i<E.size();i++){
        if (E[i].first == 0){
            int di = dist[E[i].second.first][E[i].second.second];
            T1.Modify(E[i].second.second, di + E[i].second.first - E[i].second.second);
            T2.Modify(E[i].second.second, di + E[i].second.first + E[i].second.second);
        }
        else{
            int &di = dist[E[i].second.first][E[i].second.second];

            Ckmin(di, T1.Query(1,E[i].second.second)-E[i].second.first+E[i].second.second);

            Ckmin(di, T2.Query(E[i].second.second,n)-E[i].second.first-E[i].second.second);
        }
    }
}

void mian(){
    for (int i = 0;i < Maxn * Maxn;i++){
        pos[i].clear();
    }
    n = read(); k = read();
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            a[i][j] = read();
            pos[a[i][j]].pb(mp(i,j));
            dist[i][j] = 1e9;
        }
    }
    for (int i = 1; i <= k;i ++){
        if (pos[i].empty()){
            printf("-1\n");
            return;
        }
    }
    
    for (auto v : pos[1]){
        dist[v.first][v.second] = 0;
    }

    for (int i = 2;i <= k;i ++){

        vector<pair<int,pair<int,int> > > E;

        for (auto v : pos[i - 1]) E.pb(mp(0,v));
        for (auto v : pos[i]) E.pb(mp(1,v));

        Solve(E);
    }

    int ans = 1e9;

    for (auto v : pos[k]){
        ans = min(ans, dist[v.first][v.second]);
    }

    printf("%d\n", ans);
}
int main(){
    int T = read();
    while (T --){
        mian();
    }
}