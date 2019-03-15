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

struct Matrix
{
	int x[2][2];
};

const int INF = 1000000000;
const int _n = 100000 + 10;
int n, m;
int x[_n];
int edgenum;
int vet[2 * _n], nextx[2 * _n], head[_n];
Matrix tree[4 * _n];
int times;
int fa[_n], dfn[_n], size[_n];
int top[_n], len[_n];
int g[_n][2];

void add(int u, int v)
{
	edgenum++;
	vet[edgenum] = v;
	nextx[edgenum] = head[u];
	head[u] = edgenum;
}

Matrix operator * (const Matrix x, const Matrix y)
{
	Matrix tmp;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			tmp.x[i][j] = -INF;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				tmp.x[i][k] = std::max((long long)tmp.x[i][k], (long long)x.x[i][j] + y.x[j][k]);
			}
		}
	}
	return tmp;
}

void change(int k, int l, int r, int pos, int g0, int g1)
{
	if (l == r)
	{
		tree[k].x[0][0] = g0;
		tree[k].x[0][1] = g0;
		tree[k].x[1][0] = g1;
		tree[k].x[1][1] = -INF;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)
	{
		change(k << 1, l, mid, pos, g0, g1);
	}
	else
	{
		change(k << 1 | 1, mid + 1, r, pos, g0, g1);
	}
	tree[k] = tree[k << 1] * tree[k << 1 | 1];
}

Matrix query(int k, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		return tree[k];
	}
	int mid = (l + r) >> 1;
	if (! (L <= mid))
	{
		return query(k << 1 | 1, mid + 1, r, L, R);
	}
	if (! (R > mid))
	{
		return query(k << 1, l, mid, L, R);
	}
	return query(k << 1, l, mid, L, R) * query(k << 1 | 1, mid + 1, r, L, R);
}

void dfs(int u, int father)
{
	fa[u] = father;
	size[u] = 1;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != father)
		{
			dfs(v, u);
			size[u] += size[v];
		}
	}
}

void dfs2(int u, int chain)
{
	g[u][0] = 0;
	g[u][1] = x[u];
	len[chain]++;
	top[u] = chain;
	times++;
	dfn[u] = times;
	int ch = 0;
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != fa[u])
		{
			if (size[v] > size[ch])
			{
				ch = v;
			}
		}
	}
	if (ch)
	{
		dfs2(ch, chain);
	}
	for (int i = head[u]; i; i = nextx[i])
	{
		int v = vet[i];
		if (v != fa[u] && v != ch)
		{
			dfs2(v, v);
			Matrix tmp = query(1, 1, n, dfn[v], dfn[v] + len[v] - 1);
			g[u][0] += std::max(0, std::max(tmp.x[0][0], tmp.x[1][0]));
			g[u][1] += std::max(0, tmp.x[0][0]);
		}
	}
	change(1, 1, n, dfn[u], g[u][0], g[u][1]);
}

void solve(int u, int newvalue)
{
	for (int i = top[u]; fa[i]; i = top[fa[i]])
	{
		Matrix tmp = query(1, 1, n, dfn[i], dfn[i] + len[i] - 1);
		g[fa[i]][0] -= std::max(0, std::max(tmp.x[0][0], tmp.x[1][0]));
		g[fa[i]][1] -= std::max(0, tmp.x[0][0]);
	}
	g[u][1] -= x[u];
	x[u] = newvalue;
	g[u][1] += x[u];
	change(1, 1, n, dfn[u], g[u][0], g[u][1]);
	for (int i = top[u]; fa[i]; i = top[fa[i]])
	{
		Matrix tmp = query(1, 1, n, dfn[i], dfn[i] + len[i] - 1);
		g[fa[i]][0] += std::max(0, std::max(tmp.x[0][0], tmp.x[1][0]));
		g[fa[i]][1] += std::max(0, tmp.x[0][0]);
		change(1, 1, n, dfn[fa[i]], g[fa[i]][0], g[fa[i]][1]);
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
	dfs2(1, 1);
	while (m--)
	{
		int x = read();
		int newvalue = read();
		solve(x, newvalue);
		Matrix tmp = query(1, 1, n, dfn[1], dfn[1] + len[1] - 1);
		printf("%d\n", std::max(tmp.x[0][0], tmp.x[1][0]));
	}
	return 0;
}
