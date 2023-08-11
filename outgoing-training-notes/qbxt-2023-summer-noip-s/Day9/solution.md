### 清北学堂 Day 9 总结

------------

## 材料准备

- 题目链接：[LINK](https://noip.ac/rs/problemset/show/257)

## 题解 & 思路

### T1

- 题目内容 

	小 A 对代数计算非常不擅长，现在他拿到了一个代数式，其中共有 $n$ 个未知数，每个未知数由一个单独的小写字母(可以是 a-z 之间的任意一个字母)表示且每个未知数最多出现一次。

	现在小 A 又拿到了 $n$ 个值 $v_1,v_2,\cdots,v_n$, 他需要把这 $n$ 个值按照某个顺序分配给 $n$ 个未知数，使得最终代数式的和为 $m$. 你需要帮助小 $A$ 判断是否可行。
    
- 思路分析

	由于数据规模较小，怎么搞都能过。
   
   先把式子转化成后缀表达式，然后全排列代入计算即可。
    
- 赛时 AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read_int() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			w=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		s=10*s+ch-'0';
		ch=getchar();
	}
	return s*w;
}
int v[10],cbmp[30];
bool ctong[30];
char cset[30];
signed main() {
	int t=read_int();
	for(int t1=1; t1<=t; t1+=1) {
		memset(ctong,0,sizeof(ctong));
		int n=read_int();
		for(int i=1; i<=n; i+=1) {
			v[i]=read_int();
		}
		sort(v+1,v+1+n);
		int m=read_int();
		string s;
		cin>>s;
		int ls=s.length();
		int cnt=0;
		for(int i=0; i<ls; i+=1) {
			if(s[i]>='a'&&s[i]<='z') {
				ctong[s[i]-'a']=true;
			}
		}
		for(int i=0; i<30; i+=1) {
			if(ctong[i]==true) {
				cnt+=1;
				cset[cnt]=i+'a';
				cbmp[i]=cnt;
			}
		}
		string hzbds;
		stack<char> fh;
		for(int i=0; i<ls; i+=1) {
			if(s[i]=='(') {
				fh.push('(');
			}
			if(s[i]>='a'&&s[i]<='z') {
				hzbds+=s[i];
			}
			if(s[i]==')') {
				while(true) {
					if(fh.top()!='(') {
						hzbds+=fh.top();
						fh.pop();
					} else {
						fh.pop();
						break;
					}
				}
			}
			if(s[i]=='+'||s[i]=='-'||s[i]=='*') {
				if(fh.empty()==true) {
					fh.push(s[i]);
				}
				if(fh.top()=='(') {
					fh.push(s[i]);
				}
			}
		}
		bool flag=false;
		while(!flag) {
			int l=hzbds.length();
			int isb=0;
			stack<int> res;
			while(isb<l) {
				char ch=hzbds[isb];
				isb+=1;
				if(ch>='a'&&ch<='z') {	
					int vt=v[cbmp[ch-'a']];
					res.push(vt);
				} else if(ch=='+') {
					int x=res.top();
					res.pop();
					int y=res.top();
					res.pop();
					res.push(x+y);
				} else if(ch=='-') {
					int x=res.top();
					res.pop();
					int y=res.top();
					res.pop();
					res.push(y-x);
				} else if(ch=='*') {
					int x=res.top();
					res.pop();
					int y=res.top();
					res.pop();
					res.push(x*y);
				}
			}
			if(res.top()==m) {
				flag=true;
				break;
			}
					     if(next_permutation(v+1,v+1+n)==false) {
				break;
			}
		}
		if(flag==true) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}
```

### T2

- 题目内容
	
   KAKURASU 是一个益智游戏，但是玩起来非常的坐牢！

	游戏的规则非常简单，给定一个 $n\times m$ 的方格, 你需要给每个方格染黑色或白色。 第 $i$ 行第 $j$ 列的格子如果被染成黑色会给第 $i$ 行贡献 $j$ 的点数，给第 $j$ 列贡献 $i$ 的点数，如果染成白色则不会贡献任何点数。

	最后要求第 $i$ 行总点数为 $r_i$, 第 $j$ 列总点数为 $c_j$, 你需要给出一种满足条件的染色方法。
    
- 题解

	考虑暴力搜索每个位置放了还是没放，下面开始剪枝：
    
   1. 如果某一行/某一列超过限制了或者全选了也不够，直接剪枝
	2. 从最后一行/最后一列开始搜索，因为权值大能够对后面有比较大的影响。
   
   能过。


### T3

由于 ~~难度问题~~ 我太菜了 ，实在不会做了……

### T4

打表题……

考虑搜索平方之前的数,我们可以发现如果确定了一个后缀那么平方之后的一个后缀也确定了，同时如果确定了一个前缀，平方之后的前缀也能规范到一个区间里面。

于是我们就可以按照后面一个数前面一个数的顺序进行搜索，如果某个时刻确定的后缀没有办法匹配当前的前缀区间就剪枝。

然后打表……

## 标程

见 GitHub 仓库。