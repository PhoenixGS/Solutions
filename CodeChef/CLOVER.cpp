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

const int _n = 100000 + 10;
int n, q;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int fa[_n][22], maxx[_n][22];
int ans[_n];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
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
	maxx[u][0] = x[u];
	for (int i = 1; i <= 20; i++)
	{
		maxx[u][i] = std::max(maxx[u][i - 1], maxx[fa[u][i - 1]][i - 1]);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
		}
	}
}

int query(int u, int key)
{
	for (int i = 20; i >= 0; i--)
	{
		if (maxx[u][i] < key)
		{
			u = fa[u][i];
		}
	}
	return x[u] >= key ? u : -1;
}

int main()
{
	n = read();
	q = read();
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u++;
		v++;
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	ans[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		ans[i] = query(fa[i][0], x[i] - x[1]);
	}
	while (q--)
	{
		int u;
		scanf("%d", &u);
		u++;
		if (ans[u] == -1)
		{
			puts("-1");
		}
		else
		{
			printf("%d %d\n", ans[u] - 1, x[ans[u]]);
		}
	}
	return 0;
}
