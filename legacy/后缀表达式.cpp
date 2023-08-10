#include <bits/stdc++.h>
using namespace std;
stack<int>data;
char ch;
int This_Number,x,y;
int main(){
    while(ch!='@'){
        ch=getchar();
        if(ch=='.'){
			data.push(This_Number);
			This_Number=0;
		}else if(ch>='0'&&ch<='9'){
			This_Number=This_Number*10+ch-48;
    	}else if(ch=='+'){
			x=data.top();
			data.pop();
			y=data.top();
			data.pop();
			data.push(x+y);
		}else if(ch=='-'){
			x=data.top();
			data.pop();
			y=data.top();
			data.pop();
			data.push(y-x);
		}else if(ch=='*'){
			x=data.top();
			data.pop();
			y=data.top();
			data.pop();
			data.push(x*y);
		}else if(ch=='/'){
			x=data.top();
			data.pop();
			y=data.top();
			data.pop();
			data.push(y/x);
		}
    }
    printf("%d\n",data.top());
    return 0;
}
