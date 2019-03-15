#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

long long read()
{
	char last = '+', ch = getchar();
	while (ch < '0' || ch > '9') last = ch, ch = getchar();
	long long tmp = 0;
	while (ch >= '0' && ch <= '9') tmp = tmp * 10 + ch - 48, ch = getchar();
	if (last == '-') tmp = -tmp;
	return tmp;
}

const int INF = 1000000000;
const int _n = 50000 + 10;
int n;
int nn;
int x[2 * _n];
int edgenum;
int vet[4 * _n], val[4 * _n], nextx[4 * _n], head[2 * _n];
std::vector<int> vec[_n];
int f[2 * _n];
int vis[2 * _n];
int top[2];
std::pair<int, int> v[2][2 * _n];
int size[2 * _n];
int root;
long long ans;

void add(int u, int v, int cost = 0)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs1(int u, int father)
{
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs1(v, u);
			vec[u].push_back(v);
		}
	}
}

void getroot(int u, int father, int sum, int &root)
{
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[i >> 1])
		{
			getroot(v, u, sum, root);
			f[i >> 1] = std::max(size[v], sum - size[v]);
			if (f[i >> 1] < f[root >> 1])
			{
				root = i;
			}
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int father, int minx, int deep, int cas)
{
/*	top[cas]++;
	v[cas][top[cas]] = std::make_pair(minx, deep);*/
	minx = std::min(minx, x[u]);
	if (u <= n)
	{
		top[cas]++;
		v[cas][top[cas]] = std::make_pair(minx, deep);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father && ! vis[i >> 1])
		{
			dfs2(v, u, minx, deep + cost, cas);
		}
	}
}

void solve(int u, int sum)
{
	int root = 0;
	getroot(u, 0, sum, root);
	if (! root)
	{
		return;
	}
	vis[root >> 1] = 1;
	top[0] = top[1] = 0;
	for (int i = 0; i < 2; i++)
	{
		dfs2(vet[root ^ i], 0, INF, 0, i);
		std::sort(v[i] + 1, v[i] + top[i] + 1);
	}
	for (int k = 0; k < 2; k++)
	{
		for (int i = top[k], j = top[k ^ 1], maxlen = -INF; i >= 1; i--)
		{
			while (j && v[k ^ 1][j].first >= v[k][i].first)
			{
				maxlen = std::max(maxlen, v[k ^ 1][j].second);
				j--;
			}
			ans = std::max(ans, (long long)v[k][i].first * (v[k][i].second + val[root] + maxlen + 1));
		}
	}
	solve(vet[root], size[vet[root]]);
	solve(vet[root ^ 1], sum - size[vet[root]]);
}

int main()
{
	n = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		u = read();
		v = read();
		add(u, v);
		add(v, u);
	}
	dfs1(1, 0);
	edgenum = 1;
	memset(head, 0, sizeof(head));
	nn = n;
	for (int i = 1; i <= n; i++)
	{
		if ((int)vec[i].size() <= 2)
		{
			for (int j = 0; j < (int)vec[i].size(); j++)
			{
				add(i, vec[i][j], 1);
				add(vec[i][j], i, 1);
			}
		}
		else
		{
			int pre = i;
			for (int j = 0; j < (int)vec[i].size() - 2; j++)
			{
				add(pre, vec[i][j], 1);
				add(vec[i][j], pre, 1);
				nn++;
				x[nn] = x[i];
				add(pre, nn, 0);
				add(nn, pre, 0);
				pre = nn;
			}
			add(pre, vec[i][vec[i].size() - 2], 1);
			add(vec[i][vec[i].size() - 2], pre, 1);
			add(pre, vec[i][vec[i].size() - 1], 1);
			add(vec[i][vec[i].size() - 1], pre, 1);
		}
	}
	ans = -(long long)INF * INF;
	f[0] = INF;
	solve(1, nn);
	printf("%lld\n", ans);
	return 0;
}
