#include <iostream>
#include <stdio.h>
#define MAXN 100010

using namespace std;

int n , k , a[ MAXN ] , cnt[ MAXN * 4 ] , v[ MAXN ] , tot;
long long ans = 0;

int main()
{
	//freopen( "data9.in" , "r" , stdin );
	//freopen( "data9.out" , "w" , stdout );
	cin >> n >> k;
	for( int i = 1 ; i <= k ; i++ )
		if( k % i == 0 )
			v[ ++tot ] = i;
	for( int i = 1 ; i <= n ; i++ )
	{
		cin >> a[i];
		a[i] ^= a[i - 1];
	}
	cnt[0]++;
	for( int i = 1 ; i <= n ; i++ )
	{
		for( int j = 1 ; j <= tot ; j++ )
			ans += cnt[ a[i] ^ v[j] ];
		cnt[ a[i] ]++;
	}
	cout << ans << endl;
	return 0;
}
