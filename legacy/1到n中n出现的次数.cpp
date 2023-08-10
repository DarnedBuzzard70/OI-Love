#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;
int main() {
	long long int n;
	int x=1;
	cin>>n;
	stringstream words;
	for(n++;--n;words<<n){
	}
	string s = words.str();
	cout<<count(s.begin(),s.end(),x+'0');
	return 0;
}

