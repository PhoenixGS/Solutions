#include <cstdio>
#include <cmath>
#include <cstring>
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
const int _n = 100000 + 10;
int T;
int n;
int edgenum;
int vet[_n * 2], val[_n * 2], nextx[_n * 2], head[_n];
int S, root;
int size[_n];
int f[_n];
std::vector<int> vec[_n];
int maxx[_n];
int g[_n];
int vis[_n];
long long ans;

int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x % y);
}

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
	f[u] = std::max(f[u], S - size[u]);
	if (f[u] < f[root])
	{
		root = u;
	}
}

void update(int deep, int g, int cas)
{
	for (int i = 0; i < (int)vec[g].size(); i++)
	{
		int v = vec[g][i];
		if (cas == 0)
		{
			ans = std::max(ans, (long long)v * (deep + maxx[v]));
		}
		if (cas == 1)
		{
			maxx[v] = std::max(maxx[v], deep);
		}
		if (cas == -1)
		{
			maxx[v] = 0;
		}
	}
}

void dfs(int u, int father, int deep, int cas)
{
	size[u] = 1;
	update(deep, g[u], cas);
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father && ! vis[v])
		{
			g[v] = gcd(g[u], cost);
			dfs(v, u, deep + 1, cas);
			size[u] += size[v];
		}
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
			g[v] = cost;
			dfs(v, u, 1, 0);
			dfs(v, u, 1, 1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (! vis[v])
		{
			g[v] = cost;
			dfs(v, u, 1, -1);
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (! vis[v])
		{
			S = size[v];
			root = 0;
			getroot(v, u);
			solve(root);
		}
	}
}

int main()
{
	for (int i = 1; i <= 100000; i++)
	{
		for (int j = 1; j <= sqrt(i); j++)
		{
			if (i % j == 0)
			{
				vec[i].push_back(j);
				if (j * j != i)
				{
					vec[i].push_back(i / j);
				}
			}
		}
	}
	scanf("%d", &T);
	while (T--)
	{
		ans = 0;
		scanf("%d", &n);
		edgenum = 0;
		memset(head, 0, sizeof(head));
		for (int i = 1; i < n; i++)
		{
			int u, v, c;
			u = read();
			v = read();
			c = read();
			add(u, v, c);
			add(v, u, c);
		}
		memset(vis, 0, sizeof(vis));
		f[0] = INF;
		S = n;
		root = 0;
		getroot(1, 0);
		solve(root);
		printf("%lld\n", ans);
	}
	return 0;
}
