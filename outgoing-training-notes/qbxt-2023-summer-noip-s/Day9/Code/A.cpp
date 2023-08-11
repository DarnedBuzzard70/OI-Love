#include <iostream>
#include <vector>
using namespace std;
#define loop(i, a, n) for (int i = a; i < int(n); ++i)
vector<int> v;
string s;
 
int rec(int& sind, int& vind){
    int left, right;
    char op;
    if (s[++sind] == '('){
        left = rec(sind, vind);
    } else {
        left = v[vind++];
    }
    op = s[++sind];
    if (s[++sind] == '('){
        right = rec(sind, vind);
    } else {
        right = v[vind++];
    }
    sind++; // char ')'
    switch(op){
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        default:
            cerr << "FUCKKKK!\n";
            exit(1);
            return -1;
    }
}
 
void solve(int n){
    v = vector<int>(n);
    loop(i, 0, n) cin >> v[i];
    sort(v.begin(), v.end());
    int m; cin >> m;
    cin >> s;
    //cerr << s<<endl;
    if(s.size() == 1){
        cout << (v[0] == m ? "YES" : "NO") << endl;
        return;
    }
    bool ok = false;
    do{
        int sind = 0, vind =0;
        int res = rec(sind, vind);
        //cerr << "values = "; for(int a : v) cerr << a << " ";
        //cerr << "res = " << res << endl;
        if (res == m){
            ok = true;
        }
    }
    while(!ok && next_permutation(v.begin(),v.end()));
    cout << (ok ? "YES" : "NO") << endl;
}
 
int main(){
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--){
        int n; cin >> n;
        solve(n);
    }
    return 0;
}