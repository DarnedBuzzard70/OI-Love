#include<iostream>
using namespace std;
int main() {
	int sum=0;
	for(int i=0; i<100; i+=1) {
		sum+=i+1;
	}
	cout<<sum;
	return 0;
}
