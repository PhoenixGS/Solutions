#include <cstdio>
#include <algorithm>

const int INF = 1e9;
int edgenum;
int vet[400000];
int val[400000];
int nextx[400000];
int head[300000];
int son[300000];
int f[300000];
int dis[300000];
int d[300000];
int t[2000000];
int root;
int n, K;
int sum;
int ans;
bool flag[300000];

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
	son[u] = 1;
	f[u] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! flag[v])
		{
			getroot(v, u);
			f[u] = std::max(f[u], son[v]);
			son[u] += son[v];
		}
	}
	f[u] = std::max(f[u], sum - son[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void calc(int u, int father)
{
	if (dis[u] <= K)
	{
		ans = std::min(ans, d[u] + t[K - dis[u]]);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father && ! flag[v])
		{
			d[v] = d[u] + 1;
			dis[v] = dis[u] + cost;
			calc(v, u);
		}
	}
}

void addx(int u, int father, int ff)
{
	if (dis[u] <= K)
	{
		if (ff)
		{
			t[dis[u]] = std::min(t[dis[u]], d[u]);
		}
		else
		{
			t[dis[u]] = INF;
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && ! flag[v])
		{
			addx(v, u, ff);
		}
	}
}

void solve(int u)
{
	flag[u] = 1;
	t[0] = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! flag[v])
		{
			d[v] = 1;
			dis[v] = cost;
			calc(v, 0);
			addx(v, 0, 1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! flag[v])
		{
			addx(v, 0, 0);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! flag[v])
		{
			root = 0;
			sum = son[v];
			getroot(v, 0);
			solve(root);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &K);
	for (int i = 1; i < n; i++)
	{
		int u, v, cost;
		scanf("%d%d%d", &u, &v, &cost);
		u++;
		v++;
		add(u, v, cost);
		add(v, u, cost);
	}
	for (int i = 1; i <= K; i++)
	{
		t[i] = INF;
	}
	ans = INF;
	sum = n;
	f[0] = INF;
	root = 0;
	getroot(1, 0);
	solve(root);
	if (ans == INF)
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n", ans);
	}
	return 0;
}
