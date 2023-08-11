#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[1000005];
int s[1000005];
int l[1000005];
int p[1000005][25];
int main(){
	//freopen("data.txt","r",stdin);
	//freopen("tt.out","w",stdout);
    ios::sync_with_stdio(0);
    //memset(p,127,sizeof(p));
	cin>>n>>m>>k;
	for(int i=1;n>=i;i++)cin>>a[i];
	for(int i=1;n>=i;i++){
		s[i]=s[i-1]+a[i];
	}
	for(int i=1;n>=i;i++){
		int t=lower_bound(s+1,s+n+1,s[i-1]+k)-s;
		while(s[t]-s[i-1]>k)t--;
		while(s[t]-s[i-1]<=k&&t<=n)t++;
		l[i]=t;
		//cout<<l[i]<<" ";
	}
	//cout<<endl;
	for(int i=1;n>=i;i++)p[i][0]=l[i];
	for(int i=1;21>=i;i++)
		for(int j=1;n>=j;j++)
			p[j][i]=p[p[j][i-1]][i-1];
	int x,y,ans,cnt,t,flg;
	for(int i=1;m>=i;i++){
		cin>>x>>y;
        ans=1;
        t=x;
        flg=0;
        for(int j=21;j>=0;j--)
            if(p[t][j]<=y&&p[t][j]){
				//cout<<t<<endl;
				if(t==p[t][j])flg=1;
                t=p[t][j];ans+=(1<<j);
            }
        if(flg)cout<<"Chtholly"<<endl;
        else cout<<ans<<endl;
	}
    return 0;
} 
