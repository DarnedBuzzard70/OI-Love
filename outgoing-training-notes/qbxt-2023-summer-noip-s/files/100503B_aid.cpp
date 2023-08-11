#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 9, POWN = (1 << MAXN), MAXS = 100;
int sumx[MAXN][MAXN], sumy[MAXN][MAXN], ans[MAXN][MAXN],
    usedx[MAXN][MAXN], usedy[MAXN][MAXN],
    lenx[MAXN][MAXN], leny[MAXN][MAXN], fb[POWN], n, m;
char wh[MAXN][MAXN], dp[MAXS][MAXN][POWN];
vector< pair<int, int> > p;

bool getDp(int sum, int len, int used) {
    if(dp[sum][len][used] != -1)
        return dp[sum][len][used];
    if(!sum) {
        if(!len)
            return (dp[sum][len][used] = true);
        return (dp[sum][len][used] = false);
    }
    if(!len)
        return (dp[sum][len][used] = false);
    for(int i = 0; i < 9 && i + 1 <= sum; i++)
        if(!(used & (1 << i)) && getDp(sum - i - 1, len - 1, (used | (1 << i))))
            return (dp[sum][len][used] = true);
    return (dp[sum][len][used] = false);
}

bool brute(int pos) {
    if(pos == (int)p.size())
        return true;
    int x = p[pos].first, y = p[pos].second;
    if(!getDp(sumx[x][y], lenx[x][y], usedx[x][y]) ||
       !getDp(sumy[x][y], leny[x][y], usedy[x][y]))
        return false;
    int used = (usedx[x][y] | usedy[x][y]);
    while(fb[used] + 1 <= sumx[x][y] && fb[used] + 1 <= sumy[x][y]) {
        int i = fb[used];
        used = (used | (1 << i));
        if(!getDp(sumx[x][y] - i - 1, lenx[x][y] - 1,
                  (usedx[x][y] | (1 << i))) ||
           !getDp(sumy[x][y] - i - 1, leny[x][y] - 1,
                  (usedy[x][y] | (1 << i))))
            continue;
        sumx[x + 1][y] = sumx[x][y] - i - 1;
        usedx[x + 1][y] = (usedx[x][y] | (1 << i));
        sumy[x][y + 1] = sumy[x][y] - i - 1;
        usedy[x][y + 1] = (usedy[x][y] | (1 << i));
        if(brute(pos + 1)) {
            ans[x][y] = i + 1;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            string s;
            in >> s;
            if(s[0] == '.') {
                p.push_back(make_pair(i, j));
                wh[i][j] = true;
            }
            else {
                if(s[0] != 'X')
                    sumx[i + 1][j] = (s[0] - '0') * 10 + (s[1] - '0');
                if(s[3] != 'X')
                    sumy[i][j + 1] = (s[3] - '0') * 10 + (s[4] - '0');
            }
        }
    for(int i = n - 1; i >= 0; i--)
        for(int j = m - 1; j >= 0; j--) {
            lenx[i][j] = (wh[i + 1][j]? lenx[i + 1][j] : 0) + 1;
            leny[i][j] = (wh[i][j + 1]? leny[i][j + 1] : 0) + 1;
        }
    for(int i = 0; i < MAXS; i++)
        for(int j = 0; j < MAXN; j++)
            for(int k = 0; k < POWN; k++)
                dp[i][j][k] = -1;
    for(int i = 0; i < POWN; i++)
        for(int j = 0; j < 9; j++)
            if(!(i & (1 << j))) {
                fb[i] = j;
                break;
            }
    fb[POWN - 1] = MAXS;
    brute(0);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            if(ans[i][j])
                out << ans[i][j] << ' ';
            else
                out << "_ ";
        out << '\n';
    }
    return 0;
}