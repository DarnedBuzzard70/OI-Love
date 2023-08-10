#include <bits/stdc++.h>
using namespace std;
int main() {
	int temp=0;
	for(int i=1;i<=10;i++){
		int sum=1;
		for(int j=1;j<=i;j++){
			sum*=j;
		}
		temp+=sum;
	}
	printf("%d",temp);
	return 0;
}
