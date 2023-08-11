#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define vi vector<int>
#define vpii vector<pii>
#define SZ(x) ((int)(x.size()))
#define DBG cerr << "debug here" << endl;
#define DBGV(vari) cerr << #vari<< " = "<< (vari) <<endl;

#define assertRange(x,a,b) assert((a) <= (x) and (x) <= (b))
typedef long long ll;
const int INF = 1e9;

const int N = 1e4;
const int K = 100;
const int W = 1000;
const int M = 1e5;

int d[N];
bool visited[N];

vector<pii> g[N];

using elem = pair<int, int>;

void dfs(int v) {
    visited[v] = 1;
    for (auto e : g[v]) {
        int u = e.fi;
        if (visited[u]) continue;
        dfs(u);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int tests = 1;
    //cin >> tests;
    for (int tid = 1; tid <= tests; ++tid) {
        int n;
        cin >> n;
        assertRange(n, 1, N);
        int k;
        cin >> k;
        assertRange(k, 1, K);
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            d[i] = INF;
            visited[i] = 0;
        }
        d[0] = 0;
        int m;
        cin >> m;
        assertRange(m, 1, M);
        for (int i = 0; i < m; ++i) {
            int v, u, w;
            cin >> v >> u >> w;
            assertRange(v, 1, n);
            assertRange(u, 1, n);
            assertRange(w, 1, W);
            --v, --u;
            g[v].pb({u, w});
            g[u].pb({v, w});
        }

        // asserting for connectivity
        dfs(0);
        assert(visited[n-1]);
        for (int i = 0; i < n; ++i) visited[i] = 0;

        priority_queue<elem, vector<elem>, greater<elem>> q;
        q.push({0,0});
        while (!q.empty()) {
            int v = q.top().se;
            int dst = q.top().fi;
            q.pop();
            if (visited[v]) continue;
            visited[v] = 1;
            if (v == n-1) {
                cout << dst << endl;
                break;
            }
            for (auto e : g[v]) {
                auto u = e.fi;
                auto w = e.se;
                int newd = dst+w;
                int x = dst/k;
                if (x % 2 == 1) {
                    int r = dst%k;
                    newd += k-r;
                }
                q.push({newd, u});
            }
        }
    }
    return 0;
}