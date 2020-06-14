#include <cstdio>
#include <algorithm>

const int INF = 1000000000;
const int _n = 10000 + 10, _m = 100 + 10;
int n, m;
int ques[_m];
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int root, sum;
int size[_n], f[_n];
int vis[_n], dis[_n];
int cnt[10000000 + 10];
int ans[_m];

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
			size[u] += size[v];
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
			if (dis[u] <= ques[i])
			{
				ans[i] = ans[i] | cnt[ques[i] - dis[u]];
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
		return;
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! vis[v])
		{
			dfs(v, u, cas);
		}
	}
	if (dis[u] <= 10000000)
	{
		cnt[dis[u]] += cas;
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
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add(u, v, w);
		add(v, u, w);
	}
	for (int i = 1; i <= m; i++)
	{
		scanf("%d", &ques[i]);
	}
	cnt[0] = 1;
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
