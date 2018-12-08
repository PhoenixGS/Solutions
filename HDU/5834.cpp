#include <cstdio>
#include <cstring>
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

const int _n = 100000 + 10;
int T;
int n;
int x[_n];
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int f[_n][2], g[_n][2];
int ans[_n];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs1(int u, int father)
{
	f[u][0] = x[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			dfs1(v, u);
			f[u][0] += std::max(0, f[v][0] - 2 * cost);
		}
	}
	f[u][1] = f[u][0];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			f[u][1] = std::max(f[u][1], f[u][0] - std::max(0, f[v][0] - 2 * cost) + std::max(0, f[v][1] - cost));
		}
	}
}

void dfs2(int u, int father)
{
	ans[u] = std::max(f[u][0] + g[u][1], f[u][1] + g[u][0]);
	int maxx = 0;
	int maxy = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			int tmp = std::max(0, f[v][1] - cost) - std::max(0, f[v][0] - 2 * cost);
			if (tmp > maxx)
			{
				maxy = maxx;
				maxx = tmp;
			}
			else
			{
				if (tmp > maxy)
				{
					maxy = tmp;
				}
			}
		}
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			int tmp = std::max(0, f[v][1] - cost) - std::max(0, f[v][0] - 2 * cost);
			g[v][0] = std::max(0, f[u][0] - std::max(0, f[v][0] - 2 * cost) + std::max(0, g[u][0]) - 2 * cost);
			if (tmp == maxx)
			{
				g[v][1] = std::max(0, f[u][0] - std::max(0, f[v][0] - 2 * cost) + maxy + std::max(0, g[u][0]) - cost);
			}
			else
			{
				g[v][1] = std::max(0, f[u][0] - std::max(0, f[v][0] - 2 * cost) + maxx + std::max(0, g[u][0]) - cost);
			}
			g[v][1] = std::max(g[v][1], f[u][0] - std::max(0, f[v][0] - 2 * cost) + std::max(0, g[u][1]) - cost);
			dfs2(v, u);
		}
	}
}

int main()
{
	T = read();
	int cas = 0;
	while (T--)
	{
		cas++;
		n = read();
		edgenum = 0;
		memset(head, 0, sizeof(head));
		for (int i = 1; i <= n; i++)
		{
			x[i] = read();
		}
		for (int i = 1; i < n; i++)
		{
			int u, v, cost;
			u = read();
			v = read();
			cost = read();
			add(u, v, cost);
			add(v, u, cost);
		}
		memset(ans, 0, sizeof(ans));
		dfs1(1, 0);
		dfs2(1, 0);
		printf("Case #%d:\n", cas);
		for (int i = 1; i <= n; i++)
		{
			printf("%d\n", ans[i]);
		}
	}
	return 0;
}
