#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define foreach(it, v) for(auto it=(v).begin(); it != (v).end(); ++it)

using namespace std;
const int LOGN = 15;
const int N = 1 << LOGN;
const int M = 1 << LOGN;

int n, m;
int a[N];

vector<int> g[N];

vector<pair<pii, int> > q;
int type[M], lc[M];

int p[LOGN][N], lvl[N];

int LCA(int x, int y){
    if(lvl[x] < lvl[y]) swap(x,y);

    int tmp = 1;
    while((1<<tmp) <= lvl[x]) tmp++;
    tmp--;

    for(int i = tmp; i >= 0; i--) 
        if(lvl[x] - (1<<i) >= lvl[y]) x = p[i][x];

    if(x == y) return y;

    for(int i = tmp; i >= 0; i--)
        if(p[i][x] > 0 and p[i][x] != p[i][y]) x = p[i][x], y = p[i][y];

    return p[0][x];
}

void makeTable(){
    for(int i = 1; i < LOGN; i++){
        for(int j = 1; j <= n; j++){
            p[i][j] = p[i-1][p[i-1][j]];
        }
    }
}

int st[N], ex[N], tme;

void dfs(int x, int pr){
    st[x] = tme++, p[0][x] = pr;

    foreach(it, g[x]){
        if(*it == pr) continue;

        lvl[*it] = lvl[x] + 1;
        dfs(*it, x);
    }

    ex[x] = tme++;
}

int root;
bool cmp(const pair<pii, int> &p1, const pair<pii, int> &p2){
    int x = p1.fi.fi / root, y = p2.fi.fi / root;
    if(x == y){
        return p1.fi.se < p2.fi.se;
    }
    return x < y;
}

int line[2*N];
int active[N];

ll ans[M];
ll curans;

const int MAXNUM = 10 * 1000 * 1000;

int f[MAXNUM];
vector<int> pr[MAXNUM];

vector<int> primes;

const int L = sqrt(MAXNUM);
const int K = 3;

void getPrimes(){
    primes.pb(2);
    for(int i = 3; i <= L; i += 2){
        bool ok = true;
        for(auto &x : primes){
            if(i%x == 0){
                ok = false; break;
            }
        }
        if(ok) primes.pb(i);
    }

    for(int i = 1; i <= n; i++){
        if(!pr[a[i]].empty()) continue;

        int num = a[i];
        for(auto &x: primes){
            if(num % x == 0) pr[a[i]].pb(x);
            while(num % x == 0) num /= x;
        }

        if(num > 1) pr[a[i]].pb(num);

        int sz = pr[a[i]].size();

        assert(sz <= K);
    }

}

void rem(int x);
void add(int x);

void add(int x){
    int val = line[x];
    if(active[val]){
        rem(x);
    }
    else{
        active[val] = 1;

        int sz = pr[a[val]].size();
        for(int i = 0; i < (1 << sz); i++){
            int num = 1, par = 0;
            for(int j = 0; j < sz; j++){
                if(i&(1<<j)) num *= pr[a[val]][j], par ^= 1;
            }
            if(par) curans -= f[num]++;
            else curans += f[num]++;
        }
    }
}

void rem(int x){
    int val = line[x];
    if(active[val]){
        active[val] = 0;

        int sz = pr[a[val]].size();
        for(int i = 0; i < (1 << sz); i++){
            int num = 1, par = 0;
            for(int j = 0; j < sz; j++){
                if(i&(1<<j)) num *= pr[a[val]][j], par ^= 1;
            }
            if(par) curans += --f[num];
            else curans -= --f[num];
        }
    }
    else{
        add(x);
    }
}

int main(){
    scanf("%d %d",&n,&m);

    assert(1 <= n and n <= 25000);
    assert(1 <= m and m <= 25000);

    for(int i = 1; i <= n; i++){
        scanf("%d",&a[i]);
        assert(a[i] <= 10000000);
    }

    getPrimes();

    for(int i = 1; i < n; i++){
        int u, v; scanf("%d %d",&u,&v);
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 1);
    makeTable();

    for(int i = 0; i < m; i++){
        int u, v; scanf("%d %d",&u,&v);
        if(st[u] > st[v]) swap(u,v);

        int lca = LCA(u,v);
        lc[i] = lca;

        if(lca == u){
            type[i] = 1;
            q.pb(mp(mp(st[u], st[v]), i));
        }
        else{
            type[i] = 2;
            q.pb(mp(mp(ex[u], st[v]), i));
        }
    }

    root = sqrt(2*n);
    sort(q.begin(), q.end(), cmp);

    for(int i = 1; i <= n; i++){
        line[st[i]] = i;
        line[ex[i]] = i;
    }

    for(int i = q[0].fi.fi; i <= q[0].fi.se; i++){
        add(i);
    }

    int xx = q[0].fi.fi, yy = q[0].fi.se;

    for(int i = 0; i < m; i++){
        int nx = q[i].fi.fi, ny = q[i].fi.se;

        while(xx < nx) rem(xx++);
        while(xx > nx) add(--xx);
        while(yy < ny) add(++yy);
        while(yy > ny) rem(yy--);

        ll tmp = 0;
        if(type[q[i].se] == 2){
            int node = lc[q[i].se];

            vector<int> &pd = pr[a[node]];

            int sz = pd.size();

            for(int i = 0; i < (1 << sz); i++){
                int num = 1, par = 0;
                for(int j = 0; j < sz; j++){
                    if(i&(1<<j)) num *= pd[j], par ^= 1;
                }
                if(par) tmp -= f[num];
                else tmp += f[num];
            }
        }

        ans[q[i].se] = curans + tmp;
    }

    for(int i = 0; i < m; i++){
        assert(ans[i] >= 0);
        printf("%lld\n", ans[i]);
    }

    return 0;
}