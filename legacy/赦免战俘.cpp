#include<bits/stdc++.h>
using namespace std;
#define re register
const int N=101010;
const int qwq=303030;
const int inf=0x3f3f3f3f;
int n;
int a[1234][1234];
int main()
{
	scanf("%d",&n);
	n = (1<<n);
	a[0][n+1] = 1;
	for(re int i=1;i<=n;++i)
	{
		for(re int j=1;j<=n;++j)
		{
			a[i][j] = a[i-1][j] ^ a[i-1][j+1];
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

