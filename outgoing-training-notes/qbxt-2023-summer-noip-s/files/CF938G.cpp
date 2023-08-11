#include <bits/stdc++.h>

using namespace std;

typedef pair<pair<int, int>, int> edge;

#define x first
#define y second

const int M = 2000043;
const int N = 200043;
const int B = 30;
const int IDX = 200002;

int* where[M];
int val[M];
int st = 0;

inline void rollback(int new_st)
{
	while(st != new_st)
	{
		st--;
		(*where[st]) = val[st];
	}
}

inline void change(int& address, int new_val)
{
	where[st] = &address;
	val[st] = address;
	st++;
	address = new_val;
}

vector<edge> T[4 * N];
vector<edge> Q[4 * N];
int ans[N];

void add_edge(int v, int l, int r, int L, int R, edge e)
{
	if (L >= R)
		return;
	if (l == L && r == R)
	{
		T[v].push_back(e);
		return;
	}
	int mid = (l + r) >> 1;
	add_edge(v * 2 + 1, l, mid, L, min(mid, R), e);
	add_edge(v * 2 + 2, mid, r, max(L, mid), R, e);
}

int base[B];

inline void try_gauss(int v)
{
	for(int i = 29; i >= 0; i--)
		if (base[i] != -1 && (v & (1 << i)))
			v ^= base[i];
	if (v != 0)
		for(int i = 29; i >= 0; i--)
			if (v & (1 << i))
				return change(base[i], v);
}

int rnk[N];
int dsu[N];
int dist[N];

inline int get_p(int x)
{	
	while(dsu[x] != x)
		x = dsu[x];
	return x;
}

inline int get_dist(int x)
{
	int res = 0;
	while(dsu[x] != x)
	{
		res ^= dist[x];
		x = dsu[x];
	}
	return res;
}

inline bool merge(int x, int y, int d)
{
	int dist_x = get_dist(x);
	int dist_y = get_dist(y);
	x = get_p(x);
	y = get_p(y);
	if (x == y)
		return false;
	d ^= (dist_x ^ dist_y);
	if (rnk[x] < rnk[y])
		swap(x, y);
	change(dsu[y], x);
	change(rnk[x], rnk[x] + rnk[y]);
	change(dist[y], d);
	return true;
}

inline void process(int v)
{
	for(auto x : T[v])
		if (!merge(x.x.x, x.x.y, x.y))
		{
			int cycle_len = x.y ^ get_dist(x.x.x) ^ get_dist(x.x.y);
			try_gauss(cycle_len);
		}
}

inline int answer(int x, int y)
{
	int d = get_dist(x) ^ get_dist(y);
	for(int i = 29; i >= 0; i--)
		if (base[i] != -1 && (d & (1 << i)))
			d ^= base[i];
	return d;
}

void dfs(int v, int l, int r)
{
	int rollback_to = st;
	process(v);
	if (l == r - 1)
	{
		for(auto x : Q[v])
			ans[x.y] = answer(x.x.x, x.x.y);
	}
	else
	{
		int mid = (l + r) >> 1;
		dfs(v * 2 + 1, l, mid);
		dfs(v * 2 + 2, mid, r);		
	}
	rollback(rollback_to);
}

void add_query(int v, int l, int r, int pos, edge e)
{
	if (l == r - 1)
		Q[v].push_back(e);
	else
	{
		int mid = (l + r) >> 1;
		if (pos < mid)
			add_query(v * 2 + 1, l, mid, pos, e);
		else
			add_query(v * 2 + 2, mid, r, pos, e);
	}
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
	{
		dsu[i] = i;
		dist[i] = 0;
		rnk[i] = 1;
	}
	int cur = 0;
	map<pair<int, int>, pair<int, int> > z;
	for(int i = 0; i < m; i++)
	{
		int x, y, d;
		scanf("%d %d %d", &x, &y, &d);
		--x;
		--y;
		z[make_pair(x, y)] = make_pair(0, d);
	}
	int cnt_q = 0;
	int q;
	scanf("%d", &q);
	for(int i = 0; i < q; i++)
	{
		int t;
		scanf("%d", &t);
		if (t == 1)
		{
			int x, y, d;
			scanf("%d %d %d", &x, &y, &d);
			cur++;
			--x;
			--y;
			z[make_pair(x, y)] = make_pair(cur, d);
		}
		if (t == 2)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			--x;
			--y;
			cur++;
			add_edge(0, 0, IDX, z[make_pair(x, y)].x, cur, make_pair(make_pair(x, y), z[make_pair(x, y)].y));
			z.erase(make_pair(x, y));
		}
		if (t == 3)
		{
			int x, y;
			scanf("%d %d", &x, &y);
			--x;
			--y;
			add_query(0, 0, IDX, cur, make_pair(make_pair(x, y), cnt_q));
			cnt_q++; 
		}
	}
	cur++;
	for(auto x : z)
		add_edge(0, 0, IDX, x.y.x, cur, make_pair(x.x, x.y.y));
	dfs(0, 0, IDX);
	for(int i = 0; i < cnt_q; i++)
		printf("%d\n", ans[i]);
	return 0;
}