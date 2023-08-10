#include<bits/stdc++.h>
using namespace std;
int n,num[10005],Fmax,ans[10005];
int main(){
scanf("%d",&n);
for(int i=1;i<=n;i++){scanf("%d",&num[i]);if(num[i]>Fmax)Fmax=num[i];}
for(int i=0;i<=Fmax;i++)for(int j=1;j<=n;j++)if(num[j]==i)ans[i]++;
for(int i=0;i<=Fmax;i++)printf("%d\n",ans[i]);
return 0;
}