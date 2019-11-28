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

const int _n = 10000 + 10;
int T, n;
int edgenum;
int vet[2 * _n], val[2 * _n], nextx[2 * _n], head[_n];
int fa[_n][22], deep[_n], dist[_n];
char s[100];

void add(int u, int v, int cost)
{
	edgenum++;
	vet[edgenum] = v;
	val[edgenum] = cost;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void dfs(int u, int father)
{
	fa[u][0] = father;
	for (int i = 1; i <= 20; i++)
	{
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		int cost = val[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dist[v] = dist[u] + cost;
			dfs(v, u);
		}
	}
}

int query_lca(int x, int y)
{
	if (deep[x] < deep[y])
	{
		std::swap(x, y);
	}
	for (int i = 20; i >= 0; i--)
	{
		if ((1 << i) & (deep[x] - deep[y]))
		{
			x = fa[x][i];
		}
	}
	if (x == y)
	{
		return x;
	}
	for (int i = 20; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		//init
		edgenum = 0;
		for (int i = 1; i <= n; i++)
		{
			head[i] = 0;
		}

		n = read();
		for (int i = 1; i < n; i++)
		{
			int u = read();
			int v = read();
			int cost = read();
			add(u, v, cost);
			add(v, u, cost);
		}
		dfs(1, 0);
		scanf("%s", s + 1);
		while (s[2] != 'O')
		{
			if (s[2] == 'I')
			{
				int u = read();
				int v = read();
				int lca = query_lca(u, v);
				printf("%d\n", dist[u] + dist[v] - 2 * dist[lca]);
			}
			else
			{
				int u = read();
				int v = read();
				int k = read();
				int lca = query_lca(u, v);
				if (k <= deep[u] - deep[lca] + 1)
				{
					k = k - 1;
					int t = u;
					for (int i = 20; i >= 0; i--)
					{
						if ((1 << i) & k)
						{
							t = fa[t][i];
							k -= (1 << i);
						}
					}
					printf("%d\n", t);
				}
				else
				{
					k = (deep[v] - deep[lca]) - (k - (deep[u] - deep[lca] + 1));
					int t = v;
					for (int i = 20; i >= 0; i--)
					{
						if ((1 << i) & k)
						{
							t = fa[t][i];
							k -= (1 << i);
						}
					}
					printf("%d\n", t);
				}
			}
			scanf("%s", s + 1);
		}
	}
	return 0;
}
