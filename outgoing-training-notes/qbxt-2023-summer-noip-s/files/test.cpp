#include<iostream>
using namespace std;
#define LL __int128
#define pb push_back
#define mp make_pair
bool isp(LL tmp){
    string s;
    while (tmp){
        s+=(char)(tmp%10+'0');
        tmp/=10;
    }
    string t=s;
    reverse(t.begin(),t.end());
    return s==t;
}
string toS(LL tmp){
    string s;
    while (tmp){
        s+=(char)(tmp%10+'0');
        tmp/=10;
    }
    reverse(s.begin(),s.end());
    return s;
}
const int N = 16;
int a[N];
vector<LL> res;
void check(){
    LL tmp=0;
    for (int i=0;i<N;i++) tmp=tmp*10+a[i];
    if (isp(tmp*tmp)){
        cerr<<"OKK"<<endl;
        res.pb(tmp);
    }
}
LL back(LL tmp,int len){
    string s;
    while (tmp){
        s+=(char)(tmp%10+'0');
        tmp/=10;
    }
    while (s.size()!= len) s+='0';
    LL ret = 0;
    for (int i=0;i<s.size();i++) ret = ret * 10 + (s[i]- '0');

    return ret;
}
bool match(LL L,LL R,LL B, int len){
    if (B % 10 == 0) return false;
    B = back(B, len);
    LL C = B;

    while (C <= R){
        if (!(C > R || L > B)){
            return true;
        }
        B = B * 10 + 9, C = C * 10;
    } 
    return false;
}
bool bad(int l,int r){
    if (l <= 1) return false;
    LL tmp = 0, mod = 1;
    for (int i = r + 1; i < N; i++){
        mod = mod * 10;
        tmp = tmp * 10 + a[i];
    }
    tmp = tmp * tmp % mod;

    LL lf = 0;
    for (int i = 0; i < l; i++){
        lf = lf * 10 + a[i];
    }

    LL Mn = lf * lf, Mx = (lf + 1) * (lf + 1);

    string A = toS(Mn), B=toS(Mx);
    int id = -1;
    for (int i=0;i< A.size();i++){
        if (A[i]!=B[i]){
            break;
        }
        id = i;
    }
    if (id==-1) return false;

    string T = A.substr(0, id+1);

    if (!match(Mn, Mx, tmp, N - r - 1)){
        return true;
    }
    return false;
}
void go(int l,int r,int f){

    if (l > r){
        check();
        return;
    }
    //cerr<<123<<endl;
    if (bad(l, r)){
        //cerr<<"RRR"<<endl;
        return;
    }
    //cerr<<l<<' '<<r<<' '<<f<<endl;
    if (f==0){
        int st = (l==0)?1:0;
        for (int i = st; i < 10; i++){
            a[l] = i;
            go(l+1,r, f^1);
            a[l] = 0;
        }
    }
    else{
        for (int i = 0; i < 10; i++){
            a[r] = i;
            go(l ,r - 1 , f^1);
            a[r] = 0;
        }
    }
}
int main(){
    go(0, N - 1, 0);

    sort(res.begin(),res.end());
    for (auto v : res){
        cout<<toS(v)<<' '<<toS(v*v)<<endl;
    }
}