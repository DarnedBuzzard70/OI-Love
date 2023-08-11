#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    
    std::vector<int64_t> s(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> s[i], s[i] += s[i - 1];

    const int C = std::__lg(n) + 1;
    int next[n + 2][C];
    {
        std::map<int64_t, int> last;
        int min = n + 1;
        for (int i = n; i >= 0; --i) {
            next[i][0] = min = std::min(min, !last.count(s[i]) ? n + 1 : last[s[i]]);
            last[s[i]] = i;
        }
        next[n + 1][0] = n + 1;
        for (int i = n + 1; i >= 0; --i) for (int c = 1; c < C; ++c) next[i][c] = next[next[i][c - 1]][c - 1];
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        --l;
        int ans = 0;
        for (int c = C - 1; c >= 0; --c) if (next[l][c] <= r) l = next[l][c], ans += 1 << c;
        std::cout << ans << '\n';
    }
    
    return 0;
}