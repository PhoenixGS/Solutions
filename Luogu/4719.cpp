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

struct matrix
{
	int x[2][2];

	int * operator [] (int pos)
	{
		return x[pos];
	}
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n, m;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
int fa[_n], deep[_n], size[_n];
int times;
int dfn[_n];
int top[_n], down[_n];
int g[_n][2];
matrix tree[4 * _n];

matrix operator * (matrix x, matrix y)
{
	matrix tmp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tmp[i][j] = -INF;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				tmp[i][k] = std::max((long long)tmp[i][k], (long long)x[i][j] + y[j][k]);
			}
		}
	}
	return tmp;
}

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

void pushup(int k)
{
	tree[k] = tree[k << 1] * tree[k << 1 | 1];
}

void change_(int k, int l, int r, int pos, matrix newvalue)
{
	if (l == r)
	{
		tree[k] = newvalue;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change_(k << 1, l, mid, pos, newvalue);
	}
	else
	{
		change_(k << 1 | 1, mid + 1, r, pos, newvalue);
	}
	pushup(k);
}

matrix query_(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
	int mid = (l + r) >> 1;
	if (! (L <= mid))
	{
		return query_(k << 1 | 1, mid + 1, r, L, R);
	}
	if (! (R > mid))
	{
		return query_(k << 1, l, mid, L, R);
	}
	return query_(k << 1, l, mid, L, R) * query_(k << 1 | 1, mid + 1, r, L, R);
}

void dfs(int u, int father)
{
	size[u] = 1;
	fa[u] = father;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			deep[v] = deep[u] + 1;
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int father, int chain)
{
	times++;
	dfn[u] = times;
	top[u] = chain;
	down[chain] = u;
	int k = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && size[v] > size[k])
		{
			k = v;
		}
	}
	if (k != 0)
	{
		dfs2(k, u, chain);
	}
	g[u][0] = 0;
	g[u][1] = x[u];
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father && v != k)
		{
			dfs2(v, u, v);
			matrix z = query_(1, 1, n, dfn[v], dfn[down[v]]);
			g[u][0] = g[u][0] + std::max(z[0][0], z[1][0]);
			g[u][1] = g[u][1] + z[0][0];
		}
	}
	matrix tmp;
	tmp[0][0] = g[u][0];
	tmp[0][1] = g[u][0];
	tmp[1][0] = g[u][1];
	tmp[1][1] = -INF;
	change_(1, 1, n, dfn[u], tmp);
}

void change(int u, int newvalue)
{
	g[u][1] -= x[u];
	x[u] = newvalue;
	g[u][1] += x[u];
	while (u)
	{
		int chain = top[u];
		matrix z = query_(1, 1, n, dfn[chain], dfn[down[chain]]);
		g[fa[chain]][0] -= std::max(z[0][0], z[1][0]);
		g[fa[chain]][1] -= z[0][0];
		matrix tmp;
		tmp[0][0] = g[u][0];
		tmp[0][1] = g[u][0];
		tmp[1][0] = g[u][1];
		tmp[1][1] = -INF;
		change_(1, 1, n, dfn[u], tmp);
		z = query_(1, 1, n, dfn[chain], dfn[down[chain]]);
		g[fa[chain]][0] += std::max(z[0][0], z[1][0]);
		g[fa[chain]][1] += z[0][0];
		u = fa[chain];
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		x[i] = read();
	}
	for (int i = 1; i < n; i++)
	{
		int u = read();
		int v = read();
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	dfs2(1, 0, 1);
	while (m--)
	{
		int pos, newvalue;
		scanf("%d%d", &pos, &newvalue);
		change(pos, newvalue);
		matrix z = query_(1, 1, n, 1, dfn[down[1]]);
		printf("%d\n", std::max(z[0][0], z[1][0]));
	}
	return 0;
}
