#include<bits/stdc++.h>
using namespace std;
stack <int> data;
bool biaoji[105];
char s[105];
int main(){
	cin >> s;
	int len = strlen(s);
	int k;
	for(int i = 0;i < len;i ++){
		if(s[i] == ']'){
			if(data.empty()){
				continue;
			}
			k = data.top();
			if(s[k] == '['){
				biaoji[k]=true;
				biaoji[i]=true;
				data.pop();
			}
		}else if(s[i] == ')'){
			if(data.empty()){
				continue;
			}
			k = data.top();
			if(s[k] == '('){
				biaoji[k]=true;
				biaoji[i]=true;
				data.pop();
			}
		}
		else{
			data.push(i);
		}	
	}
	for(int i = 0;i < len;i ++){
		if(biaoji[i]==true){
			cout << s[i];
		}else{
			if(s[i] == '(' || s[i] == ')'){
				printf("()");
			}else{
				printf("[]");
			}
		}
	}
	return 0;
}
