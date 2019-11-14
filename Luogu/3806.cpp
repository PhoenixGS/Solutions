#include <cstdio>
#include <algorithm>

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
const int _n = 10000 + 10;
int n, m;
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int vis[_n];
int size[_n], f[_n];
int dis[_n];
int sum, root;
int z[10000000 + 10];
int x[200], ans[200];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void getroot(int u, int father)
{
	size[u] = 1;
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			getroot(v, u);
			size[u] += size[u];
			f[u] = std::max(f[u], size[v]);
		}
	}
	f[u] = std::max(f[u], sum - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
} 

void dfs(int u, int father, int cas)
{
	if (cas == 0)
	{
		for (int i = 1; i <= m; i++)
		{
			if (dis[u] <= x[i])
			{
				ans[i] = ans[i] | z[x[i] - dis[u]];
			}
		}
	}
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father && ! vis[v])
		{
			dis[v] = dis[u] + cost;
			dfs(v, u, cas);
			size[u] += size[v];
		}
	}
	if (dis[u] <= 10000000)
	{
		z[dis[u]] += cas;
	}
}

void solve(int u)
{
	vis[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v])
		{
			dis[v] = cost;
			dfs(v, u, 0);
			dfs(v, u, 1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v])
		{
			dis[v] = cost;
			dfs(v, u, -1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! vis[v])
		{
			root = 0;
			sum = size[v];
			getroot(v, 0);
			solve(root);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		int cost = read();
		add(u, v, cost);
		add(v, u, cost);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &x[i]);
	}
	z[0] = 1;
	f[0] = INF;
	root = 0;
	sum = n;
	getroot(1, 0);
	solve(root);
	for (int i = 1; i <= m; i++)
	{
		puts(ans[i] ? "AYE" : "NAY");
	}
	return 0;
}
