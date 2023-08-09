### 清北学堂 Day 2 总结

------------

## 材料准备

- 题目链接：[LINK](https://noip.ac/rs/problemset/show/241)

## 题解 & 思路

### T1

- 直接按题解模拟即可。复杂度 $O(能过)$。

#### 赛时代码

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
const int MAXN=114;
int a[MAXN],b[MAXN];
signed main() {
	int n=read_int();
	for(int i=1;i<=n;i+=1){
		a[i]=read_int();
	}
	for(int i=1;i<=n;i+=1){
		b[i]=read_int();
	}
	int ans=0;
	for(int i=1;i<=n;i+=1){
		ans+=(a[i]-b[i])/10;
	}
	printf("%lld\n",ans);
	return 0;
}
```

### T2

- 题目内容

	有 $n$ 只青蛙排成一排青蛙序列在开会，其中第 $i$ 只青蛙的叫声大小是 $a_i$。

	对于任意两只青蛙 $i,j$，如果 $i\neq j$，则 $a_i\neq a_j$。

	现在要从青蛙中选出一支青蛙集训队，集训队的成员编号为 $0$，$1$，$...$，$k$。

	集训队要求：

	1. 对于第 $i$ 名集训队成员和第 $j$ 名集训队成员，假设 $i<j$，那一定需要满足第 $i$ 名集训队成员在青蛙序列中的位置比第 $j$ 名集训队在青蛙序列中的位置更靠前。

	2. 对于第 $i$ 名集训队成员和第 $j$ 名集训队成员，假设 $i<j$，那一定需要满足第 $i$ 名集训队成员的叫声比第 $j$ 名集训队的叫声更小。

	你需要求出有多少种选出青蛙集训队的方案。答案对 $998244353$ 取模。
    
- 题解

[![](https://pic.imgdb.cn/item/64d3a5031ddac507cca63671.jpg)](https://pic.imgdb.cn/item/64d3a5031ddac507cca63671.jpg)

### T3

- 题目内容

	有一个长度为 $n$ 的序列，第 $i$ 个位置的值为 $c_i$。

	$q$ 次询问，每次给定 $1 \leq l \leq r \leq n$，考虑子序列 $c_l, c_{l+1}, \cdots, c_{r}$，你需要选出若干个互不相交的区间，满足每个区间的元素之和为 0。要求最大化选择区间的数量，求出你可以选出多少个区间。

- 题意简化

	尽量多的选出和为 $0$ 且不相交的区间，求符合条件区间个数。
    
- 题解

[![](https://pic.imgdb.cn/item/64d3a7741ddac507ccade1fd.jpg)](https://pic.imgdb.cn/item/64d3a7741ddac507ccade1fd.jpg)

### T4

由于考试范围和难度，等我学会平衡树了再写吧……

## 标程代码

详见 Github 仓库：[LINK](https://github.com/DarnedBuzzard70/OI-Love)。
