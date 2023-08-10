#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
struct node{
    int p,d,ji;
}a[30];
int cmp(node x,node y){
    return x.p<y.p;
}
void dfs(int x,int y,int z){
    if(y<a[x+1].p||x==m){
        if(z>ans)ans=z;
        return ;
    }
    for(int i=x+1;i<=m;i++)
    if(y>=a[i].p)
    dfs(i,y-a[i].p,z+a[i].ji);
    else
    break;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
    	scanf("%d%d",&a[i].p,&a[i].d);
    	a[i].ji=a[i].d*a[i].p;
    }
    sort(a+1,a+1+m,cmp);
    dfs(0,n,0);
    cout<<ans;
    return 0;
}