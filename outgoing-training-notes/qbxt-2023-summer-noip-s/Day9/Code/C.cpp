#include<bits/stdc++.h>
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define per(i, r, l) for(int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for(int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
 
using namespace std;
 
const int N = 4, L = 4;
 
int table[7] = {1, 1, 2, 5, 14, 42};
 
int G[N][N];
bool t[N];
 
int check(int id) {
    bool can[N] = {};
    int q[N], l = 0, r = 0;
    For(i, 0, N) if(t[i]) q[r++] = i, can[i] = 1;
    while(l != r) {
        int i = q[l++];
        For(j, 0, N) if(G[j][i] && !can[j]) can[j] = 1, q[r++] = j;
    }
    int f[7][N] = {}, tot = 0;
    f[0][0] = 1;
    rep(k, 1, 6) {
        For(i, 0, N) For(j, 0, N) f[k][j] += f[k - 1][i] * G[i][j];
        int sum = 0;
        For(i, 0, N) if(t[i]) sum += f[k][i];
        if(sum > table[k]) return 0;
        tot += table[k] - sum;
    }
    bool ok = tot == 0;
    rep(i, 0, id) if(!can[i]) {
        rep(j, 0, 6) tot -= f[j][i];
        ok = 0;
    }
    return ok ? 2 : tot >= 0;
}
bool dfs1(int);
bool dfs2(int, int);
bool dfs3(int, int);
bool dfs1(int i) {
    if(i == N - (table[6] == 131)) return 0;
    t[i] = 1;
    For(j, 0, i) if(dfs2(i, j)) return 1;
    t[i] = 0;
    For(j, 0, i) if(dfs2(i, j)) return 1;
    return 0;
}
bool dfs2(int i, int j) {
    rep(k, 1, L) {
        G[j][i] = k;
        if(!check(i)) break;
        For(nj, j + 1, i) if(dfs2(i, nj)) return 1;
        if(dfs3(i, 0)) return 1;
    }
    G[j][i] = 0;
    return 0;
}
bool dfs3(int i, int j) {
    rep(nj, j, i) {
        rep(k, 1, L) {
            G[i][nj] = k;
            if(!check(i)) break;
            if(dfs3(i, nj + 1)) return 1;
        }
        G[i][nj] = 0;
    }
    if(check(i) == 2) {
        cout << i + 1 << " 20\n";
        rep(a, 0, i) cout << t[a] << ' ';
        cout << '\n';
        rep(a, 0, i) {
            int cnt = 20;
            rep(b, 0, i) while(G[a][b]--) cout << b + 1 << ' ', cnt--;
            while(cnt--) cout << "0 ";
            cout << '\n';
        }
        cout.flush();
        return 1;
    }
    return dfs1(i + 1);
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    while(cin >> table[6]) t[0] = 1, mem(G, 0), assert(dfs3(0, 0));
}