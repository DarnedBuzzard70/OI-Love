#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#define N 400005
#define inf 1000000000000007
using namespace std;
int n,m,k,q,f,s=1,tot,now=1,re;
struct node{
	int v,si,la,nx[25];
}a[N],b[N];
bool cmp(node a1,node a2){
	if(a1.v<a2.v)return 1;
	if(a1.v>a2.v)return 0;
	return a1.si<a2.si;
}
int find(int x,int t,int r,int ans){
	if(t<0)return ans;
	if(a[x].nx[t]<=r)return find(a[x].nx[t],t-1,r,ans+(1<<t));
	return find(x,t-1,r,ans);
} 
int main(){
	scanf("%d",&n);
	n++;
	b[1].si=1;
	for(int i=2;i<=n;i++){
		scanf("%d",&re);
		a[i].v=a[i-1].v+re;
		b[i].si=i;
		b[i].v=a[i].v;
	}
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(b[i].v!=b[i-1].v)continue;
		a[b[i].si].la=b[i-1].si;
	}
	for(int i=1;i<=n+1;i++)
		for(int j=0;j<=19;j++)
			a[i].nx[j]=n+1;
	for(int i=1;i<=n;i++){
		while(now<=n&&a[now].la<i)now++;
		a[i].nx[0]=now;
	}
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			a[i].nx[j]=a[a[i].nx[j-1]].nx[j-1];
	scanf("%d",&q);
	for(int i=1,l,r;i<=q;i++){
		scanf("%d%d",&l,&r);
		printf("%d\n",find(l,19,r+1,0));
	}
	return 0;
}
